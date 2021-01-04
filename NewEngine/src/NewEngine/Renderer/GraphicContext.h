#pragma once

namespace engine
{
	class GraphicContext
	{
	public:
		virtual void Init(int width, int height) = 0;
		virtual void SwapBuffers() = 0;
		virtual void Resized(int posX, int posY, int width, int height) = 0;

		static inline bool IsInitialized() { return s_Initialized; }
		static GraphicContext* MakeContext(void* window);
	private:
		static bool s_Initialized;
	};
}