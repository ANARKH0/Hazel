#include "hzpch.h"

#include "Application.h"

#include "Log.h"

// #include <GLFW/glfw3.h>  // glad.h include this
#include <glad/glad.h>

#include "Input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		HZ_CORE_ASSERT(!s_Instance, "Application already exists!")   // ����
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));   // �¼��ص�����

//		int id;
//		glGenVertexArrays(1, &(GLuint)id); // Just for test the glad.

	}

	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();

	}

	void Application::PushOverlay(Layer* overlay) {
		
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();


	}

	void Application::OnEvent(Event& e) {  // �¼���־��������

		EventDispatcher dispatcher(e); // ���ڹر��¼����Ͳ�׽ ����ȡ�¼�����

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); // ���ڹر��¼�ƥ��ö���еĴ��ڹر��¼�����رմ���

		HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {

			(*--it)->OnEvent(e);
			if (e.m_Handled) {
				break;
			}
		}

	}

	void Application::Run() {
		//WindowResizeEvent e(1280, 720);
		//HZ_TRACE(e);
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack) {

				layer->OnUpdate();
			}

			auto pos = Input::GetMousePosition();
			HZ_CORE_TRACE("{0}", "{1}", pos.first, pos.second);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;
	}

}