#pragma once

#include "../Math/Vec4.h"
#include "../Math/Mat4.h"

#include <string>
namespace Aegis {
	class Shader
	{
	public:
		explicit Shader(const std::string& file_path);
		Shader(const std::string& vertex_shader, const std::string& fragment_shader);

        ~Shader();
		
		void SetInt(const std::string& name, int value);
		void SetIntVector(const std::string& name, int count, int* values);
		void SetFloat4(const std::string& name, const Vec4& value);
		void SetMat4(const std::string& name, const Mat4& value);

		void Bind();

		unsigned int ID_ = 0;

	private:
		void CompileShaders(const std::string& vertex, const std::string& fragment);
	};

static std::string default_vertex_shader = R"(
#version 450 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TexIndex;

uniform mat4 u_Projection;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
  v_Color = a_Color;
  v_TexCoord = a_TexCoord;
  v_TexIndex = a_TexIndex;

  gl_Position = u_Projection * vec4(a_Position, 1.0);
})";	

static std::string default_fragment_shader = R"(
#version 450 core

layout (location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
    int index = int(v_TexIndex);
    if (index == 0){ o_Color = texture(u_Textures[0], v_TexCoord) * v_Color;}
    if (index == 1){ o_Color = texture(u_Textures[1], v_TexCoord) * v_Color;}
    if (index == 2){ o_Color = texture(u_Textures[2], v_TexCoord) * v_Color;}
    if (index == 3){ o_Color = texture(u_Textures[3], v_TexCoord) * v_Color;}
    if (index == 4){ o_Color = texture(u_Textures[4], v_TexCoord) * v_Color;}
    if (index == 5){ o_Color = texture(u_Textures[5], v_TexCoord) * v_Color;}
    if (index == 6){ o_Color = texture(u_Textures[6], v_TexCoord) * v_Color;}
    if (index == 7){ o_Color = texture(u_Textures[7], v_TexCoord) * v_Color;}
    if (index == 8){ o_Color = texture(u_Textures[8], v_TexCoord) * v_Color;}
    if (index == 9){ o_Color = texture(u_Textures[9], v_TexCoord) * v_Color;}
    if (index == 10){ o_Color = texture(u_Textures[10], v_TexCoord) * v_Color;}
    if (index == 11){ o_Color = texture(u_Textures[11], v_TexCoord) * v_Color;}
    if (index == 12){ o_Color = texture(u_Textures[12], v_TexCoord) * v_Color;}
    if (index == 13){ o_Color = texture(u_Textures[13], v_TexCoord) * v_Color;}
    if (index == 14){ o_Color = texture(u_Textures[14], v_TexCoord) * v_Color;}
    if (index == 15){ o_Color = texture(u_Textures[15], v_TexCoord) * v_Color;}
    if (index == 16){ o_Color = texture(u_Textures[16], v_TexCoord) * v_Color;}
    if (index == 17){ o_Color = texture(u_Textures[17], v_TexCoord) * v_Color;}
    if (index == 18){ o_Color = texture(u_Textures[18], v_TexCoord) * v_Color;}
    if (index == 19){ o_Color = texture(u_Textures[19], v_TexCoord) * v_Color;}
    if (index == 20){ o_Color = texture(u_Textures[20], v_TexCoord) * v_Color;}
    if (index == 21){ o_Color = texture(u_Textures[21], v_TexCoord) * v_Color;}
    if (index == 22){ o_Color = texture(u_Textures[22], v_TexCoord) * v_Color;}
    if (index == 23){ o_Color = texture(u_Textures[23], v_TexCoord) * v_Color;}
    if (index == 24){ o_Color = texture(u_Textures[24], v_TexCoord) * v_Color;}
    if (index == 25){ o_Color = texture(u_Textures[25], v_TexCoord) * v_Color;}
    if (index == 26){ o_Color = texture(u_Textures[26], v_TexCoord) * v_Color;}
    if (index == 27){ o_Color = texture(u_Textures[27], v_TexCoord) * v_Color;}
    if (index == 28){ o_Color = texture(u_Textures[28], v_TexCoord) * v_Color;}
    if (index == 29){ o_Color = texture(u_Textures[29], v_TexCoord) * v_Color;}
    if (index == 30){ o_Color = texture(u_Textures[30], v_TexCoord) * v_Color;}
    if (index == 31){ o_Color = texture(u_Textures[31], v_TexCoord) * v_Color;}
})";
}
