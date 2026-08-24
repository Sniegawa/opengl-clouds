cmake_minimum_required(VERSION 3.25)

project(clouds)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(clouds 
    "src/main.cpp"
    "src/app.cpp"
    "src/camera.cpp"
    "src/renderer/Renderer.cpp"
    "src/renderer/TextureHelper.cpp"
    "src/renderer/Texture.cpp"
    "src/renderer/Shader.cpp"
    "src/renderer/ComputeShader.cpp"
    "src/renderer/StorageBuffer.cpp"
    "src/renderer/UniformBuffer.cpp"
    "src/renderer/RenderContext.cpp"
    "src/renderer/ShaderResources.cpp"
    "src/renderer/passes/FullScreenQuadPass.cpp"
    "src/renderer/passes/NoisePass.cpp"
    "src/renderer/passes/CloudPass.cpp"
)

include(FetchContent)


FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

FetchContent_MakeAvailable(imgui)

target_sources(clouds PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp

    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(clouds PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)


add_library(glad STATIC
    external/glad/src/gl.c
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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_command(TARGET clouds POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/resources"
		"${CMAKE_CURRENT_BINARY_DIR}/resources"
)
