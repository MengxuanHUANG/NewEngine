#shader vertex
#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 vertexColor;

out vec4 v_Color;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0f);
	v_Color = vertexColor;
}

#shader fragment
#version 330

layout(location = 0) out vec4 color;

in vec4 v_Color;

void main()
{
	color = v_Color;
}