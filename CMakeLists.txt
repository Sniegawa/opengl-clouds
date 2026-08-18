cmake_minimum_required(VERSION 3.25)

project(clouds)

set(CMAKE_CXX_STANDARD 20)

add_executable(clouds 
    "src/main.cpp"
    "src/app.cpp"
)


add_library(glad STATIC
    external/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    external/glad/include
)


find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(clouds PRIVATE 
    glfw
    glm::glm
    glad
    OpenGL::GL    
)



