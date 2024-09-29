#shader vertex
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 aTexCoord;
out vec3 vertexColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0);
    vertexColor = color ;
    TexCoord = aTexCoord;
}



#shader fragment
#version 430 core

out vec4 color;
in vec3 vertexColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
    color = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0); 
}
