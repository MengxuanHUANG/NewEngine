#pragma once

namespace engine
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static IndexBuffer* CreateIndexBuffer(const void* index, unsigned int size);
	};
}

