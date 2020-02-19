cmake_minimum_required (VERSION 3.8)

project ("Aegis")

add_executable (Aegis 
	"src/main.cpp"
	"src/Application.cpp"
	"src/Window.cpp"
	"src/Event.h"
	"dependencies/GLAD/src/glad.c")

include_directories(
	"dependencies/GLFW/include"
	"dependencies/GLAD/include")

add_subdirectory("dependencies/GLFW")

target_link_libraries(Aegis glfw)

