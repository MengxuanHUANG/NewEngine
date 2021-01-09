#include "pch.h"
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"

#include <glad/glad.h>

namespace engine
{
	//shaders
	OpenGLShader::ShaderSource OpenGLShader::ParseShader(const std::string& filePath)
	{
		std::ifstream in(filePath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(in, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}
		in.close();
		return  { ss[0].str(), ss[1].str() };
	}
	unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);


			std::stringstream ss;

			ss << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment:") << " shader!" << std::endl;
			ss << message << std::endl;

			MY_ENGINE_ERROR(ss.str());

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	OpenGLShader::OpenGLShader(const std::string& shader_path)
		:m_FilePath(shader_path)
	{
		std::ifstream in(shader_path);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(in, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}
		in.close();

		m_RendererID = glCreateProgram();

		//Compile Vertex Shader
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, ss[0].str());
		//Compile Fragment Shader
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, ss[1].str());

		glAttachShader(m_RendererID, vs);
		glAttachShader(m_RendererID, fs);

		glLinkProgram(m_RendererID);
		glValidateProgram(m_RendererID);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	OpenGLShader::~OpenGLShader()
	{
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}
	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniformFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}
	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}
	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::SetUniformArrayi(const std::string& name, int count, const int* values)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}
	void OpenGLShader::SetUniformArray4f(const std::string& name, int count, const float* values)
	{
		glUniform4fv(GetUniformLocation(name), count, values);
	}
	void OpenGLShader::SetUniformArrayMat4f(const std::string& name, int count, const float* values)
	{
		glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, values);
	}
	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_Locations.find(name) != m_Locations.end()) return m_Locations[name];
		else 
		{
			int location = glGetUniformLocation(m_RendererID, name.c_str());
			MY_ENGINE_ASSERT(location != -1, "Wraning: uniform doesn't exit");
			m_Locations[name] = location;
			return location;
		}
	}
}