#include "hzpch.h"

#include "Application.h"

#include "Log.h"

#include <GLFW/glfw3.h>


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));   // �¼��ص�����

	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e) {  // �¼���־��������

		EventDispatcher dispatcher(e); // ���ڹر��¼����Ͳ�׽ ����ȡ�¼�����

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); // ���ڹر��¼�ƥ��ö���еĴ��ڹر��¼�����رմ���

		HZ_CORE_TRACE("{0}", e);

	}

	void Application::Run() {
		//WindowResizeEvent e(1280, 720);
		//HZ_TRACE(e);
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;
	}

}