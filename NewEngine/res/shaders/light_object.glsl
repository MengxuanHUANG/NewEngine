#shader vertex
#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float materialIndex;
layout(location = 4) in float objectIndex;

uniform mat4 u_Models[10];
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_NormalMat[10];

out float v_ObjectIndex;
out float v_MaterialIndex;
out vec3 v_Normal;
out vec3 v_Position;
out vec2 v_TexCoord;

void main()
{
	int oIndex = int(objectIndex);

	gl_Position = u_Projection * u_View * u_Models[oIndex] * vec4(position, 1.0);
	v_ObjectIndex = objectIndex;
	v_MaterialIndex = materialIndex;
	v_Normal = mat3(u_NormalMat[oIndex]) * normal;
	v_Position = mat3(u_Models[oIndex]) * position;
	v_TexCoord = texCoord;
}

#shader fragment
#version 330

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};
layout(location = 0) out vec4 color;

in float v_ObjectIndex;
in float v_MaterialIndex;
in vec3 v_Normal;
in vec3 v_Position;
in vec2 v_TexCoord;

uniform Light u_Light;
uniform vec3 u_ViewPos;

uniform float u_Shininess[10];
uniform sampler2D u_Diffuse[10];
uniform sampler2D u_Specular[10];

void main()
{
	int oIndex = int(v_ObjectIndex);
	int mIndex = int(v_MaterialIndex);
	vec3 mTexture = texture(u_Diffuse[mIndex], v_TexCoord).rgb;

	//normal vector
	vec3 normal = normalize(v_Normal);

	//ambient
	vec3 ambient = u_Light.ambient * mTexture;

	//diffuse
	vec3 lightDir = normalize( u_Light.position - v_Position);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * diff * mTexture;
	
	//specular
	vec3 viewDir = normalize(u_ViewPos - v_Position);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess[mIndex]);
	vec3 specular = u_Light.specular * (spec * texture(u_Specular[mIndex], v_TexCoord).rgb);

	float distance = length(u_Light.position - v_Position);
	float attenuation = 1.0 / (u_Light.constant + u_Light.linear * distance + u_Light.quadratic * (distance * distance));

	//result
	vec3 result = ambient + diffuse + specular;
	color = vec4(result * attenuation, 1.0);
}