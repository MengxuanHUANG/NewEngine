#pragma once

#include "NewEngine/Core/Event.h"

namespace engine
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const floatPair& motion);
		std::string ToString() const override;

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		inline float GetX() const { return m_Motion.x; }
		inline float GetY() const { return m_Motion.y; }
	private:
		floatPair m_Motion;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse| EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			:m_Button(button)
		{
		}
		int m_Button;
	};

	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button);

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int button);

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const floatPair& offset);

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		std::string ToString() const override;

		inline float GetOffsetX() const { return m_Offset.x; }
		inline float GetOffsetY() const { return m_Offset.y; }
	private:
		floatPair m_Offset;
	};
}