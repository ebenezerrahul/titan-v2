file(GLOB_RECURSE TESTBED_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)
 
add_library(testbed SHARED ${TESTBED_SOURCES})
 
target_include_directories(testbed PRIVATE ${CMAKE_SOURCE_DIR}/engine/include)
 
add_dependencies(testbed engine)

if(WIN32)
    set_target_properties(testbed PROPERTIES PREFIX "")
endif()
