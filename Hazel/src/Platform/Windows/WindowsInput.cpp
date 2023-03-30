#include "hzpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Hazel/Application.h"


namespace Hazel {

	Input* Input::s_Instacne = new WindowsInput(); // 实列化轮询输入对象，不明白为什么在这实列化


	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()); // cast the windows pointer static 
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()); // cast the windows pointer static 
		auto state = glfwGetKey(window, button);

		return state == GLFW_PRESS ;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()); // cast the windows pointer static 
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return {(float)xpos, (float)ypos};
	}

	float WindowsInput::GetMouseXImpl()
	{
		// for C++ 17 
		/*
		auto [x, y] = GetMousePositionImpl();
		return x;
		*/
		auto pos = GetMousePositionImpl();
		return pos.first;
	}

	float WindowsInput::GetMouseYImpl()
	{
		// for C++ 17 
		/*
		auto [x, y] = GetMousePositionImpl();
		return y;
		*/
		
		auto pos = GetMousePositionImpl();
		return pos.second;
	}

}