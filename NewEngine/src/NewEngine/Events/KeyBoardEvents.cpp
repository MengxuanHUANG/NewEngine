#include "pch.h"
#include "KeyBoardEvents.h"

namespace engine
{
	KeyBoardEvent::KeyBoardEvent(int keycode)
		:m_Keycode(keycode)
	{
	}
	KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount)
		:KeyBoardEvent(keycode), m_RepeatCount(repeatCount)
	{
	}
	std::string KeyPressedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_Keycode<<"["<<char(m_Keycode) << "]"<< " Pressed";
		return ss.str();
	}
	KeyReleasedEvent::KeyReleasedEvent(int keycode)
		:KeyBoardEvent(keycode)
	{
	}
	std::string KeyReleasedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_Keycode << "[" << char(m_Keycode) << "]" << " Released";
		return ss.str();
	}
	KeyTypedEvent::KeyTypedEvent(int keycode)
		:KeyBoardEvent(keycode)
	{
	}
	std::string KeyTypedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_Keycode << "[" << char(m_Keycode) << "]" << " Typed";
		return ss.str();
	}
}