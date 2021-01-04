#pragma once

#include "NewEngine/Renderer/Texture.h"

namespace engine
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& file_path);
		~OpenGLTexture();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual inline int GetWidth() const override { return m_Width; }
		virtual inline int GetHeight() const override { return m_Height; }
		virtual inline int GetBitPerPixrl() const override { return m_BPP; }
		virtual inline unsigned int GetRendererID() const override { return m_RendererID; }

	private:
		unsigned int m_RendererID;
		int m_Width, m_Height, m_BPP;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;

		unsigned int m_InternalFormat;
		unsigned int m_DataFormat;
	};
}