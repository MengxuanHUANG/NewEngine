#pragma once

#include "Layer.h"

#include <vector>

namespace engine
{
	class LayerStack
	{
	public:
		LayerStack() {}
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushSuperLayer(Layer* layer);
		void PopSuperLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Stack.begin(); }
		std::vector<Layer*>::iterator end() { return m_Stack.end(); }
	private:
		unsigned int m_StackToptIndex = 0;
		std::vector<Layer*> m_Stack;
	};
}