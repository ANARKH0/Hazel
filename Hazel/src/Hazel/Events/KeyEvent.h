#pragma once

#include "Event.h"

//#include <sstream>

namespace Hazel {


	class HAZEL_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyBoard)

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		int m_KyeCode;
	};



	class HAZEL_API KeyPressedEvent : public KeyEvent {
	public:
	KeyPressedEvent(int keycode, int repeatCount) :
		KeyEvent(keycode), m_RepeatCount(repeatCount) {}

	inline  int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToSring() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << "repeats)";
		return ss.str();
	}


	EVENT_CLASS_TYPE(KeyPressed)
	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyBoard)

	private:
		int m_RepeatCount;
	};


	class HAZEL_API KeyReleaseEvent : public Event {
	public:
		KeyReleaseEvent(int keycode) : 
			KeyEvent(keycode) {}




		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}


		EVENT_CLASS_TYPE(KeyReleased)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	};
}