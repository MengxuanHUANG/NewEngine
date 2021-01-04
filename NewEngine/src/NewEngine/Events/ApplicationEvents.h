#pragma once

#include "NewEngine/Core/Event.h"

namespace engine
{
	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() {}

		std::string ToString() const override;

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height);
		std::string ToString() const override;

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};
	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent() {}

		std::string ToString() const override;

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		inline float GetOffsetX() const { m_Motion.x; }
		inline float GetOffsetY() const { m_Motion.y; }
	private:
		floatPair m_Motion;
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		std::string ToString() const override;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		std::string ToString() const override;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		std::string ToString() const override;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}

