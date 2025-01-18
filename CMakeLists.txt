cmake_minimum_required(VERSION 3.10)
project(GeometrySlash C CXX)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
set(OPENGL_VERSION "1.1" CACHE STRING "" FORCE)


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

add_subdirectory(libs/raylib)

target_link_libraries(GeometrySlash PRIVATE raylib)

# only build libcurl if building with leaderboard support
if (SUPPORT_LEADERBOARD)
	set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE) # don't build curl executable, only library
	set(HTTP_ONLY ON CACHE BOOL "" FORCE) # only http support is needed
	set(SSL_ENABLED ON)
	set(ENABLE_UNIX_SOCKETS OFF) # not needed, we only use TCP/IP
	set(CURL_USE_LIBSSH OFF) # not needed
	set(CURL_USE_LIBSSH2 OFF) # not needed
	set(CURL_USE_LIBPSL OFF) # not needed
	set(CURL_DISABLE_CRYPTO_AUTH ON) # not needed (krb5, spnego)
	set(BUILD_LIBCURL_DOCS OFF)
	set(BUILD_MISC_DOCS OFF)


	if(APPLE)
		set(CURL_USE_SECTRANSP ON) # Deprecated darwinssl stuff from MacOS 10.3, no idea how to build with OpenSSL
	endif()

	if(WIN32)
		set(CURL_USE_SCHANNEL ON) # Required for HTTPS
	endif()
	add_subdirectory(libs/curl)
	target_compile_definitions(GeometrySlash PRIVATE SUPPORT_LEADERBOARD)
	target_link_libraries(GeometrySlash PRIVATE libcurl)
endif()


#add_compile_options(-Wall -Wextra -pedantic)

