SET(CMAKE_SYSTEM_NAME Windows)

SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER_INIT x86_64-w64-mingw32-windres)
SET(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
SET(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
SET(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

add_link_options(-static -static-libgcc -static-libstdc++)
