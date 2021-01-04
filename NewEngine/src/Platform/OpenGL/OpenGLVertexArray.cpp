#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace engine
{
	static unsigned int GetSizeOfGLType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		default:
			MY_ENGINE_ASSERT(false, "Undefined type!");
			return 0;
		}
	}
	OpenGLBufferLayout::OpenGLBufferLayout()
		:m_Stride(0)
	{
	}
	void OpenGLBufferLayout::Push(DataType type, unsigned int count)
	{
		switch (type)
		{
		case DataType::FLOAT:
			m_Attributes.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += GetSizeOfGLType(GL_FLOAT) * count;
			break;
		case DataType::UNSIGNED_INT:
			m_Attributes.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += GetSizeOfGLType(GL_UNSIGNED_INT) * count;
			break;
		case DataType::UNSIGNED_CHAR:
			m_Attributes.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_Stride += GetSizeOfGLType(GL_UNSIGNED_BYTE) * count;
			break;
		default:
			MY_ENGINE_ASSERT(false, "Undefined type!");
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::SetLayout(const VertexBuffer& vb, const VertexBufferLayout& layout) const
	{
		Bind();
		vb.Bind();

		const std::vector<Attribute> attributes = layout.GetAttributes();
		unsigned int offset = 0;

		for (int i =0; i< attributes.size(); i++)
		{
			const Attribute& attribute = attributes[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized, layout.GetStride(), (const void*)offset);
			offset += attribute.count * GetSizeOfGLType(attribute.type);
		}
	}

}