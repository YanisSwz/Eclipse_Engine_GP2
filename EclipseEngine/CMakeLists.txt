##### EclipseEngine #####

file(GLOB_RECURSE ECLIPSE_ENGINE_SOURCES "Engine/Source/*.cpp")

add_library(ECLIPSE_ENGINE SHARED ${ECLIPSE_ENGINE_SOURCES} "Engine/Source/Resource/ResourceManager.cpp" "Engine/Source/Resource/TextureExtention.cpp")

# Set C++ standard version
target_compile_features(ECLIPSE_ENGINE PRIVATE cxx_std_20)

# Set Warning level 4 and warnings as errors flags
if(MSVC)
    target_compile_options(ECLIPSE_ENGINE PRIVATE /W4 /WX)
else()
    target_compile_options(ECLIPSE_ENGINE PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()


add_subdirectory(Libs)
add_subdirectory(Engine)