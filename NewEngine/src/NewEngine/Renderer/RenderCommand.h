#pragma once

#include "NewEngine/Renderer/Renderer.h"

namespace engine
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL, Directx
	};

	class RenderCommand
	{
	public:
		static void Init();
		static void Terminate();

		static void ClearColor(glm::vec4 color);
		static void BindTextures(unsigned int first, int count, const unsigned int* textures);
		static void Draw(int count);

		static inline RendererAPI GetRendererAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;

		static Renderer3D* s_Renderer3D;
	};
}