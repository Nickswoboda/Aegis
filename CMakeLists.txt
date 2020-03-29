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
	"dependencies/GLAD/src/glad.c")

add_executable(Sandbox 
	"Sandbox/Sandbox.cpp")

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLAD/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLM/"
	"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb_image/"
	"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/FreeType/include")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLM")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/FreeType")

target_link_libraries(Aegis glfw)
target_link_libraries(Aegis freetype)

target_link_libraries(Sandbox Aegis)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})