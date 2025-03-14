##### EclipseMath #####

cmake_minimum_required(VERSION 3.16)

# Query all source files (sub-dir recursive) and stores it in MATH_LIB_SOURCES var
file(GLOB_RECURSE ECLIPSE_MATH_LIB_SOURCES "Code/Source/*.cpp")

# Create static library (.lib).
add_library(ECLIPSE_MATH STATIC ${ECLIPSE_MATH_LIB_SOURCES})

# Add public include dir.
target_include_directories(ECLIPSE_MATH PUBLIC "Code/Include")

# Set C++ standard version
target_compile_features(ECLIPSE_MATH PRIVATE cxx_std_20)

# Set Warning level 4 and warnings as errors flags
if(MSVC)
    target_compile_options(ECLIPSE_MATH PRIVATE /W4 /WX)
else()
    target_compile_options(ECLIPSE_MATH PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()


option(ECLIPSE_MATH_LIB_UNITTEST_OPT "Enable Unit Tests" ON)

# Enable GoogleTest & GLM
if (ECLIPSE_MATH_LIB_UNITTEST_OPT)
    enable_testing()
    add_subdirectory(Tests)
endif()