#type vertex

#version 330 core
layout (location = 0) in vec3 a_Position;

uniform mat4 u_Projection;
uniform mat4 u_Transform;

void main()
{
  gl_Position = u_Projection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment

#version 330 core
out vec4 FragColor;

uniform vec4 u_Color;

void main()
{
   FragColor = u_Color;
}