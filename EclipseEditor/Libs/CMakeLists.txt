##### Editor Libs #####

# ImGUI 
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ImGUI")

file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp) 
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui PUBLIC ${IMGUI_DIR}/backends)

target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(ECLIPSE_EDITOR PUBLIC imgui)