cmake_minimum_required (VERSION 3.8)

project ("Aegis")

add_library (Aegis STATIC
	"src/Application.cpp"
	"src/Window.cpp"
	"src/Event.h"
	"src/Font.cpp"
	"src/Renderer/Renderer.cpp"
	"src/Renderer/Texture.cpp"
	"src/Renderer/Shader.cpp"
	"src/Renderer/VertexArray.cpp"
	"dependencies/GLAD/src/glad.c"
	"src/Math.h" "src/Math.cpp"
	"src/KeyCodes.h" "src/MouseCodes.h")

add_executable(Sandbox 
	"Sandbox/Sandbox.cpp" "src/Math.cpp")

target_include_directories(Aegis
PUBLIC
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

target_link_libraries(Sandbox Aegis)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})