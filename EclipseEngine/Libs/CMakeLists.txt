##### Engine Libs #####

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

target_link_libraries(ECLIPSE_ENGINE PUBLIC glfw)

# EclipseMath
set(ECLIPSE_MATH_LIB_UNITTEST_OPT OFF CACHE BOOL "" FORCE)

add_subdirectory(EclipseMath)

target_link_libraries(ECLIPSE_ENGINE PUBLIC ECLIPSE_MATH)

# GLAD
add_subdirectory(Glad)
target_link_libraries(ECLIPSE_ENGINE PRIVATE glad)

# STB
target_include_directories(ECLIPSE_ENGINE PUBLIC "Stb")
