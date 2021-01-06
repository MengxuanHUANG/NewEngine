#include "pch.h"
#include "PointLight.h"

namespace engine
{
	PointLight::PointLight(glm::vec3 position, glm::vec4 color, float strength)
		:Light(position, color, strength)
	{
	}
	PointLight::~PointLight()
	{

	}
}