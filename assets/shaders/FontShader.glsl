#type vertex

#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 0) in vec2 a_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_Transform;

out vec2 TexCoord;

void main()
{
  gl_Position = u_Projection * u_Transform * vec4(a_Position, 1.0);
  TexCoord = a_TexCoord;
}

#type fragment

#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0,  texture(u_Texture, TexCoord).r );
  FragColor = sampled * u_Color;
}