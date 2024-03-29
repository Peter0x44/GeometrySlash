cmake_minimum_required(VERSION 3.0)
project(GeometrySlash CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
set(OPENGL_VERSION "1.1" CACHE STRING "" FORCE)

# Setting paramters for libcurl
set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE) # don't build curl executable, only library
set(HTTP_ONLY ON CACHE BOOL "" FORCE) # only http support is needed
set(SSL_ENABLED ON)
set(ENABLE_UNIX_SOCKETS OFF) # not needed, we only use TCP/IP
set(CURL_USE_LIBSSH OFF) # not needed
set(CURL_USE_LIBSSH2 OFF) # not needed
set(CURL_DISABLE_CRYPTO_AUTH ON) # not needed (krb5, spnego)

if(APPLE)
	set(CURL_USE_SECTRANSP ON) # Deprecated darwinssl stuff from MacOS 10.3, no idea how to build with OpenSSL
endif()

if(WIN32)
	set(CURL_USE_SCHANNEL ON) # Required for HTTPS
endif()

add_subdirectory(libs/raylib)
add_subdirectory(libs/curl)

#add_compile_options(-Wall -Wextra -pedantic)

add_executable(GeometrySlash
	src/main.cpp
	src/gamestate.cpp
	src/gamestate.h
	src/ingame.cpp
	src/ingame.h
	src/mainmenu.cpp
	src/mainmenu.h
	src/random.cpp
	src/random.h
	src/resultsscreen.cpp
	src/resultsscreen.h
	src/button.cpp
	src/button.h
	src/network.cpp
	src/network.h
	src/leaderboard.cpp
	src/leaderboard.h
)

target_link_libraries(GeometrySlash PRIVATE raylib libcurl)
