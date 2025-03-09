cmake_minimum_required(VERSION 3.30)
project(px-engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON)

# 1) Include FetchContent to manage external dependencies
include(FetchContent)
find_package(Python REQUIRED)

# 2) Fetch dependencies: GLM (public), GLFW & GLAD (private)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glm glfw glad)

# 3) Create the library target: px-engine
#    - Contains all core .cpp files except examples
add_library(px-engine STATIC
        src/engine.cpp
        src/graphics.cpp
        src/window.cpp
        src/surface.cpp
        src/input.cpp
        include/color.h
        include/keyCodes.h
)

# 4) Set public and private include directories
#    - Public: The 'include' folder (which contains engine.h)
#    - Private: The 'src' folder and GLAD headers.
target_include_directories(px-engine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${glad_SOURCE_DIR}/include
)

# 5) Link dependencies:
#    - Expose GLM publicly (for use in engine.h).
#    - Keep GLFW and GLAD private.
if (APPLE)
    target_link_libraries(px-engine
            PUBLIC glm
            PRIVATE glfw glad "-framework OpenGL"
    )
elseif (MSYS OR MINGW)
    target_link_libraries(px-engine
            PUBLIC glm
            PRIVATE glfw glad opengl32
    )
elseif (UNIX)
    target_link_libraries(px-engine
            PUBLIC glm
            PRIVATE glfw glad GL
    )
endif ()

# 6) Create the executable target for examples
add_executable(px-engine-square examples/square.cpp)
add_executable(px-engine-mandelbrot examples/mandelbrot.cpp)

# 7) Link the px-engine library to the executable
target_link_libraries(px-engine-square PRIVATE px-engine)
target_link_libraries(px-engine-mandelbrot PRIVATE px-engine)