#pragma once


namespace engine
{
	class Light
	{
	public:

		inline glm::vec3& GetPosition();
		inline glm::vec4& GetColor();

		inline const float* GetVertices() const;
		inline const unsigned int* GetIndices() const;
	};
}