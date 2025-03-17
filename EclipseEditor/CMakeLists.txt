##### EclipseEditor #####

add_executable(ECLIPSE_EDITOR "Editor/main.cpp")

target_link_libraries(ECLIPSE_EDITOR PRIVATE ECLIPSE_ENGINE)

# Set C++ standard version
target_compile_features(ECLIPSE_EDITOR PRIVATE cxx_std_20)

# Set Warning level 4 and warnings as errors flags
if(MSVC)
    target_compile_options(ECLIPSE_EDITOR PRIVATE /W4 /WX)
else()
    target_compile_options(ECLIPSE_EDITOR PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_custom_command(
TARGET ECLIPSE_EDITOR
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/Assets
$<TARGET_FILE_DIR:ECLIPSE_EDITOR>/Assets
)