#include "pch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace engine
{
	OpenGLTexture::OpenGLTexture(const std::string& file_path)
	{
		stbi_set_flip_vertically_on_load(1);

		m_LocalBuffer = stbi_load(file_path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//have to be set if applying "GL_CLAMP_TO_BORDER"
		float borderColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_LocalBuffer)
		{
			stbi_image_free(m_LocalBuffer);
		}

		glActiveTexture(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	void OpenGLTexture::BindUnit(unsigned int slot)
	{
		glBindTextureUnit(slot, m_RendererID);
	}
	void OpenGLTexture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}