#pragma once

#include "glm/glm.hpp"

namespace engine
{
	class Shader
	{
	public:
		~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual void SetUniformFloat(const std::string& name, float value) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) = 0;

		virtual void SetUniformArrayi(const std::string& name, const int* values) = 0;
		virtual void SetUniformArray4f(const std::string& name, unsigned int count, float* values) = 0;
		virtual void SetUniformArrayMat4f(const std::string& name, unsigned int count, float* values) = 0;

		static Shader* CreateShader(const std::string& shader_path);
	};
}