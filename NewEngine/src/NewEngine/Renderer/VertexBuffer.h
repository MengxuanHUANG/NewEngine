#pragma once

namespace engine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		static VertexBuffer* CreateVertexBuffer(const void* vertex, unsigned int size);
	};
}