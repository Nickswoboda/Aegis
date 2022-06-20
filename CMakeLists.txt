cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
project ("Aegis")

set(AegisSrc
	"src/Core/Application.cpp"
	"src/Core/Window.cpp"
	"src/Core/Object.cpp"
	"src/Core/Scene.cpp"
	"src/Utility/Timing.cpp" 
	"src/Utility/FontManager.cpp" 
	"src/Utility/TextureManager.cpp" 
	"src/Renderer/Camera.cpp" 
	"src/Renderer/Sprite.cpp"
	"src/Renderer/Font.cpp"
	"src/Renderer/Renderer.cpp"
	"src/Renderer/Texture.cpp"
	"src/Renderer/Shader.cpp"
	"src/Renderer/VertexArray.cpp"
	"src/Math/Vec4.cpp" 
	"src/Math/Interpolation.cpp" 
	"src/Math/Vec2.cpp" 
	"src/Math/Vec3.cpp" 
	"src/Math/Mat4.cpp"
	"src/Math/AABB.cpp"
	"src/UI/Widget.cpp"
	"src/UI/Dialog.cpp"
	"src/UI/Button.cpp" 
	"src/UI/Dropdown.cpp" 
	"src/UI/UILayer.cpp" 
	"src/UI/Container.cpp" 
	"src/UI/Checkbox.cpp"
	"src/UI/Label.cpp" 
	"src/UI/SpriteWidget.cpp"
	"src/UI/SpinBox.cpp"
	"src/Audio/AudioPlayer.cpp"
	"src/Audio/Sound.cpp")

set(DependencySrc 
	"dependencies/GLAD/src/glad.c"
	"dependencies/stb_vorbis/stb_vorbis.c")

add_library (Aegis STATIC
	${AegisSrc}
	${DependencySrc})

target_include_directories(Aegis
PUBLIC
	"src/"
	"dependencies/GLFW/include"
	"dependencies/GLAD/include"
	"dependencies/stb_image/"
	"dependencies/stb_vorbis/"
	"dependencies/FreeType/include"
	"dependencies/OpenAL-Soft/include")

add_subdirectory("dependencies/GLFW")
add_subdirectory("dependencies/FreeType")

set(LIBTYPE STATIC)
set(ALSOFT_UTILS OFF CACHE BOOL "Build utility programs")
add_subdirectory("dependencies/OpenAL-Soft")

target_link_libraries(Aegis glfw)
target_link_libraries(Aegis freetype)
target_link_libraries(Aegis OpenAL)

Set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

add_custom_command(TARGET Aegis PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:Aegis>)
