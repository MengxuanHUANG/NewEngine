#pragma once

#include "NewEngine/Renderer/Renderer.h"

namespace engine
{
	class OpenGLRenderer3D : public Renderer3D
	{
	public:
		OpenGLRenderer3D(int width, int height);
		~OpenGLRenderer3D();

		virtual void Init(int width, int height) override;
		virtual void Terminate() override;
		virtual void ClearColor(glm::vec4 color) override;
		virtual void Draw(int count) override;
	};
}