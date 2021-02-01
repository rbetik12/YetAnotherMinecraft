# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("YetAnotherMinecraft")
set(CMAKE_CXX_STANDARD 17)



# Include sub-projects.
add_subdirectory ("YetAnotherMinecraft")
add_subdirectory ("lib/glfw")
add_subdirectory ("lib/glad")
add_subdirectory ("lib/spdlog")