#pragma once

namespace engine
{
	class Renderer3D
	{
	public:
		virtual void Init(int width, int height) = 0;
		virtual void Terminate() = 0;
		virtual void ClearColor(glm::vec4 color) = 0;
		virtual void Draw(int count) = 0;

		static Renderer3D* Create3DRenderer(int width, int height);
	};
}

