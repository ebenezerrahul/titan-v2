file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)
 
add_executable(engine ${ENGINE_SOURCES})
 
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(engine PRIVATE lib ${CMAKE_DL_LIBS})
