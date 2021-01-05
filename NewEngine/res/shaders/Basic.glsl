#shader vertex
#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_VertexColor;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
	v_VertexColor = vertexColor;
	v_TexCoord = texCoord;
}

#shader fragment
#version 330

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

in vec2 v_TexCoord;
in vec4 v_VertexColor;

void main()
{
	vec4 temp = texture(u_Texture, v_TexCoord);
	color = v_VertexColor;
}