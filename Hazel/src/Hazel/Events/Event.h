#pragma once

#include "Hazel/Core.h"
#include "hzpch.h"

//#include <string>
//#include <functional>

namespace Hazel {

	// Events 是一个阻塞事件系统，目前没有缓冲和延迟，事件都是实时阻塞处理
	// 预计将来会添加延迟处理

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0), // 0000 0000
		EventCategoryInput			= BIT(1), // 0000 0001
		EventCategoryKeyboard		= BIT(2), // 0000 0010
		EventCategoryMouse			= BIT(3), // 0000 0100
		EventCategoryMouseButton	= BIT(4), // 0000 1000

	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; } 

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event {

	friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

//	protected:
		bool m_Handled = false; // 事件处理标志
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>; // 输入参数T类型的引用，返回类型bool

	public:
		EventDispatcher (Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {

			if (m_Event.GetEventType() == T::GetStaticType()) {

				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;

	};
	
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}