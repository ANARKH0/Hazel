#pragma once

#include "Hazel/Core.h"
#include "hzpch.h"

//#include <string>
//#include <functional>

namespace Hazel {

	// Events ��һ�������¼�ϵͳ��Ŀǰû�л�����ӳ٣��¼�����ʵʱ��������
	// Ԥ�ƽ����������ӳٴ���

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
							   virtual EventType GetEventtype() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; } 

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event {

	friend class EventDispatcher;

	public:
		virtual EventType GetEventtype() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false; // �¼�������־
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>; // ����������ͣ���������bool

	public:
		EventDispatcher (Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventype() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(*t)&m_Event);
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