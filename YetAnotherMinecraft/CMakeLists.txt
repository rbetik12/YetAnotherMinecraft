# CMakeList.txt : CMake project for YetAnotherMinecraft, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_compile_definitions(R_ENABLE_ASSERTS)

set(LIB "..")

include_directories(${LIB}/lib/glfw/include)
include_directories(${LIB}/lib/glad/include)
include_directories(${LIB}/lib/spdlog/include)
include_directories(${LIB}/lib/glm)

# Add source to this project's executable.
add_executable (YetAnotherMinecraft "YetAnotherMinecraft.cpp"  "Core/Window/Window.cpp" "Core/Window/Window.h" "Core/Core.h" "Core/Log.h" "Core/Log.cpp" "Core/Application.cpp" "Core/Application.h" "Core/Events/Event.h" "Core/Events/ApplicationEvent.h" "Core/Events/KeyEvent.h" "Core/Events/MouseEvent.h" "Core/Rendering/VertexArray.h" "Core/Rendering/VertexArray.cpp" "Core/Rendering/VertexBuffer.h" "Core/Rendering/VertexBuffer.cpp" "Core/Rendering/IndexBuffer.h" "Core/Rendering/IndexBuffer.cpp" "Core/Rendering/VertexBufferLayout.h" "Core/Rendering/Shader.cpp" "Core/Rendering/Renderer.h" "Core/Rendering/Renderer.cpp" "Core/Rendering/VertexBufferElement.cpp" "Core/Rendering/VertexBufferLayout.cpp" "Core/Debug/Debug.h" "Core/Debug/Debug.cpp")
target_link_libraries(YetAnotherMinecraft glad glfw glm)
# TODO: Add tests and install targets if needed.

set (source "${CMAKE_SOURCE_DIR}/YetAnotherMinecraft/Shaders")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/resources/shaders")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "copied shaders folder from ${source} => ${destination}"
)
