#pragma once

#include "VertexBuffer.h"

#include <vector>

namespace engine
{
	enum DataType
	{
		INT = 0, FLOAT, UNSIGNED_INT, UNSIGNED_CHAR
	};

	struct Attribute
	{
		unsigned int type;
		unsigned int count;
		bool normalized;
	};

	class VertexBufferLayout
	{
	public:
		friend class VertexArray;

		virtual void Push(DataType type, unsigned int count) = 0;

		virtual inline const std::vector<Attribute>& GetAttributes() const = 0;
		virtual inline unsigned int GetStride() const = 0;
		static VertexBufferLayout* CreateBufferLayout();
	};

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const VertexBuffer&, const VertexBufferLayout&) const = 0;
		static VertexArray* CreateVertexArray();
	};
}