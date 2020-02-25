cmake_minimum_required (VERSION 3.8)

project ("Aegis")

add_executable (Aegis 
	"src/main.cpp"
	"src/Application.cpp"
	"src/Window.cpp"
	"src/Event.h"
	"src/Font.cpp"
	"src/Renderer/Renderer.cpp"
	"src/Renderer/Texture.cpp"
	"src/Renderer/Shader.cpp"
	"src/Renderer/VertexArray.cpp"
	"dependencies/GLAD/src/glad.c")

include_directories(
	"dependencies/GLFW/include"
	"dependencies/GLAD/include"
	"dependencies/GLM/"
	"dependencies/stb_image/"
	"dependencies/FreeType/include")

add_subdirectory("dependencies/GLFW")
add_subdirectory("dependencies/GLM")
add_subdirectory("dependencies/FreeType")

target_link_libraries(Aegis glfw)
target_link_libraries(Aegis freetype)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})