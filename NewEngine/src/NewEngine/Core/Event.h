#pragma once
#include "pch.h"

#define BIT(x) (1<<(x))

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
	virtual EventType GetEventType() const override {return GetStaticType();}\
	virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace engine
{
	enum class EventType
	{
		None = 0,
		WindowClosed, WindowResized, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyTyped, KeyReleased,
		MouseMoved, MouseClicked, MouseScrolled, MouseButtonPressed, MouseButtonReleased
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

	struct floatPair
	{
		float x, y;
	};

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const = 0;
		inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }

		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator <<(std::ostream& out, const Event& event)
	{
		out << event.ToString();
		return out;
	}
}