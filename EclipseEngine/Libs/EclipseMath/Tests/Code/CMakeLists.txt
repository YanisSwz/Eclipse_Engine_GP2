add_executable(MATH_LIB_UT "Source/Mat4Tests.cpp" "Source/Mat3Tests.cpp" "Source/Mat2Tests.cpp" "Source/Vec4Tests.cpp" "Source/Vec3Tests.cpp" "Source/Vec2Tests.cpp" "Source/QuatTests.cpp")

target_link_libraries(MATH_LIB_UT PUBLIC MATH_LIB)

add_test(NAME C_MATH_LIB_UT COMMAND MATH_LIB_UT)