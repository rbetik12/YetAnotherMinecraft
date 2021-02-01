# CMakeList.txt : CMake project for YetAnotherMinecraft, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_compile_definitions(R_ENABLE_ASSERTS)

set(LIB "..")

include_directories(${LIB}/lib/glfw/include)
include_directories(${LIB}/lib/glad/include)
include_directories(${LIB}/lib/spdlog/include)

# Add source to this project's executable.
add_executable (YetAnotherMinecraft "YetAnotherMinecraft.cpp"  "Core/Window/Window.cpp" "Core/Window/Window.h" "Core/Core.h" "Core/Log.h" "Core/Log.cpp" "Core/Application.cpp" "Core/Application.h" "Core/Events/Event.h" "Core/Events/ApplicationEvent.h" "Core/Events/KeyEvent.h" "Core/Events/MouseEvent.h")
target_link_libraries(YetAnotherMinecraft glad glfw)
# TODO: Add tests and install targets if needed.
