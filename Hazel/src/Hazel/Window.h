#pragma once

#include "hzpch.h"

#include "Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine", 
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Width(width), Height(height) { }

	};

	class HAZEL_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;  // 无返回类型 指向Event类型对象

		virtual ~Window() = default; // 动态绑定

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enablded) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;  // not only for GLFWwindows

		static Window* Create(const WindowProps& props = WindowProps());
	};
}