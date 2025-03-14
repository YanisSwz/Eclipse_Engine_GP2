cmake_minimum_required (VERSION 3.16)

project("Eclipse Project")

# Create global variable (project-level) to store output directory
set(ECLIPSE_PROJECT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Build/${CMAKE_CXX_COMPILER_ID}_$<CONFIG>")

# Log directory at configuration-time
message("[${CMAKE_PROJECT_NAME}]: Output directory: ${ECLIPSE_PROJECT_OUTPUT_DIR}")

# Set output directory for compiled libs and exe (project-level)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ECLIPSE_PROJECT_OUTPUT_DIR}/Libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ECLIPSE_PROJECT_OUTPUT_DIR}/Libs")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ECLIPSE_PROJECT_OUTPUT_DIR}")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(EclipseEngine)
add_subdirectory(EclipseEditor)