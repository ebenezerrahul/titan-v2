# Cross-compile for 64-bit Windows from Linux using MinGW-w64.
#   Debian/Ubuntu: sudo apt install mingw-w64
#   Arch:          sudo pacman -S mingw-w64-gcc
#   Fedora:        sudo dnf install mingw64-gcc
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
 
set(MINGW_TRIPLE x86_64-w64-mingw32)
set(CMAKE_C_COMPILER   ${MINGW_TRIPLE}-gcc)
set(CMAKE_CXX_COMPILER ${MINGW_TRIPLE}-g++)
set(CMAKE_RC_COMPILER  ${MINGW_TRIPLE}-windres)
 
# Search the MinGW sysroot for libraries/headers, but the host for build tools
set(CMAKE_FIND_ROOT_PATH /usr/${MINGW_TRIPLE})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
 
# Lets CMake/CTest run the built .exe through wine automatically
set(CMAKE_CROSSCOMPILING_EMULATOR wine)
