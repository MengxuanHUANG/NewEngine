#pragma once

#include <string>

namespace engine
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void Bind() const = 0;
		virtual void BindUnit(unsigned int) = 0;
		virtual void UnBind() const = 0;

		virtual inline int GetWidth() const = 0;
		virtual inline int GetHeight() const = 0;
		virtual inline int GetBitPerPixrl() const = 0;
		virtual inline unsigned int GetRendererID() const = 0;

		static Texture* CreateTexture(const std::string& file_path);
		
		//for White Texture
		//static Texture* CreateTexture(unsigned int, unsigned int);
	};
}

