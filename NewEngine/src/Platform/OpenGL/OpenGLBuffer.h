#pragma once

#include "NewEngine/Renderer/VertexBuffer.h"
#include "NewEngine/Renderer/IndexBuffer.h"

namespace engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* vertex, unsigned int size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const void* index, unsigned int size);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
	private:
		uint32_t m_RendererID;
	};
}