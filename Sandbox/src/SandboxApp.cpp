#include "Hazel.h"

class Exampleyer : public Hazel::Layer 
{
public:
	Exampleyer() : Layer("Example") { }

	void OnUpdate() override {

		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override {

		HZ_TRACE("{0}", event);
	}

};




class Sandbox : public Hazel::Application
{
public:
	Sandbox() {

		PushLayer(new Exampleyer());

	}
	~Sandbox() {

	}

private:

};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}