cmake_minimum_required (VERSION 3.8)

project ("Aegis")

add_executable (Aegis 
	"src/main.cpp"
	"src/Application.cpp"
	"src/Window.cpp"
	"src/Event.h"
	"src/Renderer/Renderer.cpp"
	"src/Renderer/Texture.cpp"
	"src/Renderer/Shader.cpp"
	"src/Renderer/VertexArray.cpp"
	"dependencies/GLAD/src/glad.c")

include_directories(
	"dependencies/GLFW/include"
	"dependencies/GLAD/include"
	"dependencies/GLM/"
	"dependencies/stb_image/")

add_subdirectory(
	"dependencies/GLFW"
	"dependencies/GLM")

target_link_libraries(Aegis glfw)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})