cmake_minimum_required (VERSION 3.8)

project ("Aegis")

add_library (Aegis STATIC
	"src/Application.cpp"
	"src/Window.cpp"
	"src/Event.h"
	"src/Font.h"
	"src/Font.cpp"
	"src/Renderer/Renderer.cpp"
	"src/Renderer/Texture.cpp"
	"src/Renderer/Shader.cpp"
	"src/Renderer/VertexArray.cpp"
	"dependencies/GLAD/src/glad.c"
	"src/KeyCodes.h" "src/MouseCodes.h" "src/Timer.cpp" "src/Timer.h" "src/Camera.cpp" "src/Sprite.h" "src/Math/Vec4.cpp" "src/Math/Interpolation.cpp" "src/Math/Vec2.cpp" "src/Math/Vec3.cpp" "src/Math/AABB.cpp"
	"src/Math/Color.h" "src/UI/Button.cpp" "src/Scene.cpp" "src/UI/Dropdown.cpp" "src/FontManager.h"  "src/UI/UILayer.cpp" "src/UI/Container.cpp" "src/UI/Checkbox.cpp"
	"src/FontManager.cpp" "src/TextureManager.cpp")

add_executable(Sandbox 
	"Sandbox/Sandbox.cpp" "src/UI/UILayer.cpp")

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

Set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()


file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
