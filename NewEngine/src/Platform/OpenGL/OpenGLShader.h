#pragma once

#include "NewEngine/Renderer/Shader.h"

#include <string>
#include <unordered_map>

namespace engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& shader_path);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniformInt(const std::string& name, int value) override;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) override;
		virtual void SetUniformFloat(const std::string& name, float value) override;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetUniformArrayi(const std::string& name, const int* values) override;
		virtual void SetUniformArray4f(const std::string& name, unsigned int count, float* values) override;
		virtual void SetUniformArrayMat4f(const std::string& name, unsigned int count, float* values) override;

	private:
		struct ShaderSource
		{
			std::string VertexSource;
			std::string FragmentSource;
		};

		ShaderSource ParseShader(const std::string& file_path);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		int GetUniformLocation(const std::string& name);
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		std::unordered_map<std::string, unsigned int> m_Locations;
	};
}
