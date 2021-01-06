#include "pch.h"
#include "Light.h"

namespace engine
{
	Light::Light(glm::vec3 position, glm::vec4 color, float strength)
		:m_Position(position), m_Color(color), m_Strength(strength)
	{
	}
}