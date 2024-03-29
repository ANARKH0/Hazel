#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include <glad/glad.h>


namespace Hazel {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char * description) { // GLFW 错误事件日志回调

		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& prop) {

		return new WindowsWindow(prop);
	}



	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		}
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		HZ_CORE_INFO("Creating window {0} ({1},{2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {

			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // glad 接入处
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!")

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) { // lambda function

			WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);  // 使用无类型指针void接受对应窗口事件类型的指针

			data.Width = width;
			data.Height = height;

			WindowResizedEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);  // 使用无类型指针void接受对应窗口事件类型的指针
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);  // 使用无类型指针void接受对应窗口事件类型的指针
			
			switch (action) {  // key event 事件类型

				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}

				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}

			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);  // 使用无类型指针void接受对应窗口事件类型的指针

			KeyTypedEvent event(keycode);
			data.EventCallback(event);

		});




		glfwSetMouseButtonCallback(m_Window, [] (GLFWwindow* window, int button, int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);  // 使用无类型指针void接受对应窗口事件类型的指针
			
			switch (action) {  // mouse button events 混合

				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);  // 使用无类型指针void接受对应窗口事件类型的指针
			
			MouseScrolledEvent event((float)xOffset, (float)yOffset);   // 申明为float，接口定于double，故类型续强转
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [] (GLFWwindow* window, double xPos, double yPos) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);  // 使用无类型指针void接受对应窗口事件类型的指针

			MouseMovedEvent event((float)xPos, (float)yPos);	// 申明为float，接口定于double，故类型续强转
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}



}