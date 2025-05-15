##### Editor Libs #####

# ImGUI 
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ImGUI")

file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp) 
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui PUBLIC ${IMGUI_DIR}/backends)

target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(ECLIPSE_EDITOR PUBLIC imgui)

# ImGuizmo
set(IMGUIZMO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo")
file(GLOB IMGUIZMO_SOURCES ${IMGUIZMO_DIR}/ImGuizmo.cpp) 
add_library(imguizmo STATIC ${IMGUIZMO_SOURCES})
target_include_directories(imguizmo PUBLIC ${IMGUIZMO_DIR})

target_link_libraries(ECLIPSE_EDITOR PUBLIC imguizmo)

# ImPlot
set(IMPLOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ImPlot")
file(GLOB IMPLOT_SOURCES "${IMPLOT_DIR}/*.cpp") 
add_library(implot STATIC ${IMPLOT_SOURCES})
target_include_directories(implot PUBLIC ${IMPLOT_DIR})

target_link_libraries(implot PUBLIC imgui)
target_link_libraries(ECLIPSE_EDITOR PUBLIC implot)

