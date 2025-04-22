##### SoLoud #####

add_compile_definitions(WITH_WINMM)

# Query all source files (sub-dir recursive) and stores it in MATH_LIB_SOURCES var
file(GLOB_RECURSE SOLOUD_SOURCES "src/*.cpp")

# Create static library (.lib).
add_library(SoLoud STATIC ${SOLOUD_SOURCES})

# Add public include dir.
target_include_directories(SoLoud PUBLIC "include")

# Set C++ standard version
target_compile_features(SoLoud PRIVATE cxx_std_20)