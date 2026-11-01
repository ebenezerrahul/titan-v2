file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)

add_library(lib STATIC ${LIB_SOURCES})

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(WIN32)
    set_target_properties(lib PROPERTIES PREFIX "")
endif()
