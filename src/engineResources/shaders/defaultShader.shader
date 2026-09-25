#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec2 aTexCoord;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}


#shader fragment
#version 460 core

out vec4 color;
in vec2 TexCoord;

layout(binding = 0) uniform sampler2D texture1;
layout(binding = 1) uniform sampler2D texture2;

void main()
{
	color = texture2D(texture1, TexCoord);
	//color = vec4(TexCoord, 0.0, 1.0);
	//color = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.6);
}
