file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)

 
add_executable(engine ${ENGINE_SOURCES}
../tracy/public/TracyClient.cpp
)
 
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/tracy/public/tracy)
target_link_libraries(engine PRIVATE lib ${CMAKE_DL_LIBS})
if(MINGW)
    target_compile_definitions(engine PRIVATE UNICODE _UNICODE TRACY_ENABLE)
    target_link_options(engine PRIVATE -municode)
    target_link_libraries(engine PRIVATE
        ws2_32
        dbghelp
        secur32
    )
endif()
