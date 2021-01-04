#include "pch.h"
#include "LayerStack.h"

namespace engine
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Stack)
		{
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Stack.emplace(m_Stack.begin() + m_StackToptIndex, layer);
		m_StackToptIndex++;
	}
	void LayerStack::PushSuperLayer(Layer* layer)
	{
		m_Stack.emplace_back(layer);
	}
	void LayerStack::PopSuperLayer(Layer* layer)
	{
		auto it = std::find(m_Stack.begin(), m_Stack.end(), layer);
		if (it != m_Stack.end())
		{
			m_Stack.erase(it);
		}
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Stack.begin(), m_Stack.end(), layer);
		if (it != m_Stack.end())
		{
			m_Stack.erase(it);
			--m_StackToptIndex;
		}
	}
}