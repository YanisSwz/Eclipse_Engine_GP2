##### Engine Libs #####

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# add_subdirectory(glfw)

target_link_libraries(ECLIPSE_ENGINE PRIVATE glfw)

# EclipseMath
add_subdirectory(EclipseMath)