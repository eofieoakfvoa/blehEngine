#shader vertex
#version 460 core

out vec2 texCoord;
void main()
{
    float x = -1.0 + float((gl_VertexID & 1) << 2);
    float y = -1.0 + float((gl_VertexID & 2) << 1);
    texCoord = (vec2(x,y) + 1.0) *0.5;
    gl_Position = vec4(x, y, 0, 1);
}

#shader fragment
#version 460 core

in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D screenTexture;

const float offset_x = 1.0f / 800.0f;
const float offset_y = 1.0f / 800.0f;

vec2 offsets[9] = vec2[]
(
    vec2(-offset_x  , offset_y), vec2( 0.0f, offset_y)  ,vec2(offset_x, offset_y),
    vec2(-offset_x  , 0.0f), vec2( 0.0f, 0.0f)  ,vec2(offset_x, 0.0f),
    vec2(-offset_x  , -offset_y), vec2( 0.0f, -offset_y)  ,vec2(offset_x, -offset_y)
);
float kernel[9] = float[]
(
  1,1,1,
  1,-8,1,
  1,1,1
);

void main()
{

    FragColor = texture(screenTexture, texCoord);
}