#include "pch.h"
#include "ApplicationEvents.h"

namespace engine
{
	std::string WindowClosedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "WindowCloseEvent: Window closed";
		return ss.str();
	}
	WindowResizedEvent::WindowResizedEvent(unsigned int width, unsigned int height)
		:m_Width(width), m_Height(height)
	{
	}
	std::string WindowResizedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "WindowResizedEvent: Window Resized: ["<<m_Width<<", "<<m_Height<<"]";
		return ss.str();
	}
	std::string WindowMovedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "WindowMovedEvent: ["<< m_Motion.x<<", "<<m_Motion.y<<"]";
		return ss.str();
	}
	std::string AppTickEvent::ToString() const
	{
		std::stringstream ss;
		ss << "AppTickEvent: Application Tick";
		return ss.str();
	}
	std::string AppUpdateEvent::ToString() const
	{
		std::stringstream ss;
		ss << "AppUpdateEvent: Application Update";
		return ss.str();
	}
	std::string AppRenderEvent::ToString() const
	{
		std::stringstream ss;
		ss << "AppRenderEvent: Application Render";
		return ss.str();
	}
}