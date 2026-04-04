cmake_minimum_required(VERSION 3.10)
project(openGLinit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Added 'ON' here

# 1. Find the package
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# 2. Define the executable FIRST
add_executable(openGLinit src/intro.cpp)

# 3. Link the libraries AFTER defining the executable
target_link_libraries(openGLinit PRIVATE
        glfw
        glad::glad # namespaced target for GLAD
)
