#include "pch.h"
#include "Light.h"

namespace engine
{
	Light::Light(glm::vec3 position, glm::vec4 color, float strength)
		:m_Position(position), m_Color(color), m_Strength(strength), m_Ambient(0.2f, 0.2f, 0.2f), m_Diffuse(0.5f, 0.5f, 0.5f), m_Specular(1.0f, 1.0f, 1.0f)
	{
	}
}