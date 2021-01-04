#include "pch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace engine
{
	OpenGLTexture::OpenGLTexture(const std::string& file_path)
	{
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &channels, 4);

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 3)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 4)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//have to be set if applying "GL_CLAMP_TO_BORDER"
		float borderColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (data)
		{
			stbi_image_free(data);
		}

		glActiveTexture(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	void OpenGLTexture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}