#include "Hazel.h"

class ExampleLayer : public Hazel::Layer 
{
public:
	ExampleLayer() : Layer("Example") { }

	void OnUpdate() override {

		HZ_INFO("ExampleLayer::Update");

		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))  // 使用Hazel的映射，摆脱对其它库的依赖，就是利用Hazel做中间转化，如对GLFW或者Win32API
		{
			HZ_INFO("Tab key is pressed(poll)!");
		}
	}

	void OnEvent(Hazel::Event& event) override {

//		HZ_TRACE("{0}", event);

		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event; // 这里是当event为按键事件时将其类型指定为键入事件，后续将记录所键入的按键的值
			if (e.GetKeyCode() == HZ_KEY_TAB)
			{
				HZ_TRACE("Tab key is pressed (event)!")
			}

			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}


	}

};




class Sandbox : public Hazel::Application
{
public:
	Sandbox() {

		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());

	}
	~Sandbox() {

	}

private:

};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}