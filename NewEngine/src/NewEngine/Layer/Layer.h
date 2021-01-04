#pragma once

#include "NewEngine/Core/Event.h"
#include <string>

namespace engine
{
	class Layer
	{
	public:
		Layer(const std::string& name);
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetech() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {}
	protected:
		std::string m_Name;
	};
}