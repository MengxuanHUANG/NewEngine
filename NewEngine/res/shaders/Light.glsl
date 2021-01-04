#shader vertex
#version 330

layout(location = 0) in vec4 position;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * position;
}

#shader fragment
#version 330

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0);
}