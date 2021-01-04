#pragma once

#include "NewEngine/Renderer/VertexArray.h"

namespace engine
{
	class OpenGLBufferLayout: public VertexBufferLayout
	{
	public:
		OpenGLBufferLayout();

		virtual void Push(DataType type, unsigned int count) override;

		virtual inline const std::vector<Attribute>& GetAttributes() const override { return m_Attributes; }
		virtual inline unsigned int GetStride() const override { return m_Stride; }
	private:
		std::vector<Attribute> m_Attributes;
		unsigned int m_Stride;
	};

	class OpenGLVertexArray: public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const VertexBuffer&, const VertexBufferLayout&) const override;
	private:
		unsigned int m_RendererID;
	};
}

