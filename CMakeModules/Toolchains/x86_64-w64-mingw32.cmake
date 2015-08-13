set(GNU_HOST x86_64-w64-mingw32)
set(CMAKE_SYSTEM_PROCESSOR "x86_64")

set(COMPILER_PREFIX "${GNU_HOST}-")

set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_CROSSCOMPILING TRUE)
set(WIN32 TRUE)
set(MINGW TRUE)

include(CMakeForceCompiler)
cmake_force_c_compiler(${COMPILER_PREFIX}gcc GNU)
cmake_force_cxx_compiler(${COMPILER_PREFIX}g++ GNU)
set(CMAKE_RC_COMPILER ${COMPILER_PREFIX}windres)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)