file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)

 
add_executable(engine ${ENGINE_SOURCES}
../tracy/public/TracyClient.cpp
)
 
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/tracy/public/tracy)

set(VULKAN_ROOT "${CMAKE_SOURCE_DIR}/third_party/vulkan/mingw64")
set(Vulkan_INCLUDE_DIR "${VULKAN_ROOT}/include")
set(Vulkan_LIBRARY "${VULKAN_ROOT}/lib/libvulkan-1.dll.a")

find_package(Vulkan REQUIRED)

target_link_libraries(engine PRIVATE lib ${CMAKE_DL_LIBS} Vulkan::Vulkan)
if(MINGW)
    target_compile_definitions(engine PRIVATE UNICODE _UNICODE TRACY_ENABLE)
    target_link_options(engine PRIVATE -municode)
    target_link_libraries(engine PRIVATE
        ws2_32
        dbghelp
        secur32
    )
endif()
