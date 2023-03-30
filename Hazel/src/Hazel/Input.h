#pragma once

#include "Core.h"

namespace Hazel {

	class HAZEL_API Input {

	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instacne->IsKeyPressedImpl(keycode);  } // API
		inline static bool IsMouseButtonPressed(int button) { return s_Instacne->IsMouseButtonPressedImpl(button); } // API
		inline static std::pair<float, float> GetMousePosition() { return s_Instacne->GetMousePositionImpl(); } // API
		inline static float GetMouseX() { return s_Instacne->GetMouseXImpl(); } // API
		inline static float GetMouseY() { return s_Instacne->GetMouseYImpl(); } // API

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;  // for dirffenece platform
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
 	private:
		static Input* s_Instacne;


	};

}