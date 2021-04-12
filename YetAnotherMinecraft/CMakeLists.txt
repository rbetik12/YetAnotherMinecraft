# CMakeList.txt : CMake project for YetAnotherMinecraft, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_compile_definitions(R_ENABLE_ASSERTS GLFW_INCLUDE_NONE)

set(LIB "..")

include_directories(${LIB}/lib/glfw/include)
include_directories(${LIB}/lib/glad/include)
include_directories(${LIB}/lib/spdlog/include)
include_directories(${LIB}/lib/glm)
include_directories(${LIB}/lib/imgui)
include_directories(${LIB}/lib/stb_image)
include_directories(${LIB}/lib/PerlinNoise)

# Add source to this project's executable.
add_executable (YetAnotherMinecraft "YetAnotherMinecraft.cpp"  "Core/Window/Window.cpp" "Core/Window/Window.h" "Core/Core.h" "Core/Log.h" "Core/Log.cpp" "Core/Application.cpp" "Core/Application.h" "Core/Events/Event.h" "Core/Events/ApplicationEvent.h" "Core/Events/KeyEvent.h" "Core/Events/MouseEvent.h" "Core/Rendering/VertexArray.h" "Core/Rendering/VertexArray.cpp" "Core/Rendering/VertexBuffer.h" "Core/Rendering/VertexBuffer.cpp" "Core/Rendering/IndexBuffer.h" "Core/Rendering/IndexBuffer.cpp" "Core/Rendering/VertexBufferLayout.h" "Core/Rendering/Shader.cpp" "Core/Rendering/Renderer.h" "Core/Rendering/Renderer.cpp" "Core/Rendering/VertexBufferElement.cpp" "Core/Rendering/VertexBufferLayout.cpp" "Core/Debug/Debug.h" "Core/Debug/Debug.cpp" "Core/UI/ImGuiBuild.cpp"  "Core/UI/ImGuiUI.h" "Core/UI/ImGuiUI.cpp" "Core/Camera/FPSCamera.h" "Core/Camera/FPSCamera.cpp" "Core/Time.h" "Core/Time.cpp" "Core/Game/Block/Block.h"  "Core/Game/Block/StoneBlock.h" "Core/Game/Block/StoneBlock.cpp" "Core/Game/Block/Block.cpp" "Core/Rendering/Texture.h" "Core/Rendering/Texture.cpp" "Core/Game/Block/BlockIds.h" "Core/Game/Chunk/Chunk.cpp" "Core/Game/Chunk/Chunk.h" "Core/Utils/RVec.h" "Core/Utils/RFloat.h")
target_link_libraries(YetAnotherMinecraft glad glfw glm imgui stb_image)
# TODO: Add tests and install targets if needed.

set (source "${CMAKE_SOURCE_DIR}/YetAnotherMinecraft/Shaders")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/resources/shaders")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "copied shaders folder from ${source} => ${destination}"
)

set (resSrc "${CMAKE_SOURCE_DIR}/resources")
set (resDest "${CMAKE_CURRENT_BINARY_DIR}/resources")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${resSrc} ${resDest} 
    COMMENT "copied resources folder from ${resSrc} => ${resDest}"
)

