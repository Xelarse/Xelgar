cmake_minimum_required(VERSION 3.20.0)
project(xelgar VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_DIR "${PROJECT_PARENT_DIR}/engine")
set(CMAKE_SOURCE_DIR ${PROJECT_DIR}/src)
set(EXECUTABLE_NAME "XelgarRun")

##Need to get the libs for this and actually put them in the libs folder
include_directories(
    ${PROJECT_DIR}/include
    ${PROJECT_PARENT_DIR}/lib/GLFW/glfw-3.3.7/include
)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${${OPENGL_gl_LIBRARY}})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})


if (UNIX)
    message("Building for UNIX")
    find_package(glfw3 REQUIRED)

elseif (APPLE)
    message("Building for APPLE")
    find_package(glfw3 REQUIRED)

elseif  (WIN32)
    message("Building for Windows")
    add_subdirectory(${PROJECT_PARENT_DIR}/lib/GLFW/glfw-3.3.7)
    add_compile_definitions(GLEW_STATIC)

else ()
    message("Platform not supported")
endif()

file(GLOB_RECURSE SOURCE_FILES_DIR ${CMAKE_SOURCE_DIR}/*.cpp)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES_DIR})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE OpenGL::GL glfw GLEW::GLEW)

#Copy over assets to the build directory
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${EXECUTABLE_NAME} copy_assets)

#This project setup looks like the exact type i want https://github.com/AliKhudiyev/LayZ-Renderer-Engine