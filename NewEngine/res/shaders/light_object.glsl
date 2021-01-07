#shader vertex
#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texSlot;
layout(location = 4) in float objectIndex;

uniform mat4 u_Models[2];
uniform mat4 u_View;
uniform mat4 u_Projection;

out float v_Index;
out vec3 v_Normal;
out vec3 v_Position;

void main()
{
	int index = int(objectIndex);

	gl_Position = u_Projection * u_View * u_Models[index] * vec4(position, 1.0);
	v_Index = objectIndex;
	v_Normal = normal;
	v_Position = mat3(transpose(inverse(u_Models[index]))) * position;
}

#shader fragment
#version 330

layout(location = 0) out vec4 color;

in float v_Index;
in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_Position;

uniform vec4 u_Color[2];
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform float u_SpecularStrength;

void main()
{
	int index = int(v_Index);

	//normal vector
	vec3 normal = normalize(v_Normal);

	//ambient
	float ambientStrength = 0.01;
	vec3 ambient = ambientStrength * u_LightColor;

	//diffuse
	vec3 lightDir = normalize( u_LightPos - v_Position);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * u_LightColor;
	
	//specular
	//float specularStrength = 0.5;
	vec3 viewDir = normalize(u_ViewPos - v_Position);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = u_SpecularStrength * spec * u_LightColor;

	//result
	color = vec4(ambient + diff + specular, 1.0) * u_Color[index];
}