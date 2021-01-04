#include "pch.h"

#include "MouseEvents.h"

namespace engine
{
	MouseScrolledEvent::MouseScrolledEvent(const floatPair& offset)
		:m_Offset(offset)
	{
	}
	std::string MouseScrolledEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: [" << m_Offset.x << ", " << m_Offset.y<<"]";
		return ss.str();
	}
	MouseMovedEvent::MouseMovedEvent(const floatPair& motion)
		:m_Motion(motion)
	{
	}
	std::string MouseMovedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: [" << m_Motion.x << ", " << m_Motion.y<<"]";
		return ss.str();
	}
	MousePressedEvent::MousePressedEvent(int button)
		:MouseButtonEvent(button)
	{
	}
	std::string MousePressedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MousePressedEvent: " << m_Button;
		return ss.str();
	}
	MouseReleasedEvent::MouseReleasedEvent(int button)
		:MouseButtonEvent(button)
	{
	}
	std::string MouseReleasedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseReleasedEvent: " << m_Button;
		return ss.str();
	}
}