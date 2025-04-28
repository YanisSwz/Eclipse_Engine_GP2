##### Engine Libs #####

include(FetchContent)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_LIBRARY_TYPE "SHARED" CACHE STRING "" FORCE)

add_subdirectory(glfw)

target_link_libraries(ECLIPSE_ENGINE PUBLIC glfw)

# EclipseMath
set(ECLIPSE_MATH_LIB_UNITTEST_OPT OFF CACHE BOOL "" FORCE)

add_subdirectory(EclipseMath)
target_link_libraries(ECLIPSE_ENGINE PUBLIC ECLIPSE_MATH)

# GLAD
add_subdirectory(Glad)
target_link_libraries(ECLIPSE_ENGINE PUBLIC glad)

# STB
target_include_directories(ECLIPSE_ENGINE PUBLIC Stb)

# TinyOBJ
target_include_directories(ECLIPSE_ENGINE PUBLIC TinyOBJ)

# Jolt
# Enable the debug renderer in the Debug and Release builds. Note that DEBUG_RENDERER_IN_DISTRIBUTION will override this setting.
option(DEBUG_RENDERER_IN_DEBUG_AND_RELEASE "Enable debug renderer in Debug and Release builds" ON)

if (NOT TARGET JoltPhysics)
    FetchContent_Declare(
            JoltPhysics
            GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
            GIT_TAG "v5.3.0"
		    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/JoltPhysics"
    )
    FetchContent_MakeAvailable(JoltPhysics)
endif()

set(PHYSICS_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/JoltPhysics")
include("${PHYSICS_REPO_ROOT}/Jolt/Jolt.cmake")
target_link_libraries(ECLIPSE_ENGINE PUBLIC Jolt)

# SoLoud
add_subdirectory(SoLoud)
target_link_libraries(ECLIPSE_ENGINE PUBLIC SoLoud)

# Meta
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(Meta)
target_link_libraries(ECLIPSE_ENGINE PUBLIC meta)