cmake_minimum_required(VERSION 3.20)
project(titan LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put the exe and the DLL in the same folder so Windows finds the DLL at runtime
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_C_VISIBILITY_PRESET hidden)
 
if(MINGW)
    add_link_options(-static)
endif()

add_subdirectory(lib)
add_subdirectory(engine)
add_subdirectory(testbed)
