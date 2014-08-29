cmake_minimum_required(VERSION 3.0.1)

if (WIN32)
	Message(STATUS "***************************************************************************")
	Message(STATUS "*                           WINDOWS USERS!!! READ THIS                    *")
	Message(STATUS "*  Your environment variables must be correct for cmake to work           *")
	Message(STATUS "*              You must run CMake as an administrator                     *")
	Message(STATUS "***************************************************************************\n\n")
ENDIF()


project(Flight)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH "${Flight_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# Set an output directory for our binaries
set(BIN_DIR ${Flight_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

MESSAGE(STATUS "FLAGS:" ${CMAKE_CXX_FLAGS})

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)

find_package(Lua51 REQUIRED)
find_package(Boost REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)


#if windows, manually fix some dependencies
IF(WIN32)
	SET(GLEW_INCLUDE_DIR $ENV{CPP_REPOSITORY}/glew/include)
	SET(GLEW_LIBRARIES $ENV{CPP_REPOSITORY}/glew/lib/glew32s.lib)
	
	SET(SDL2_IMAGE_INCLUDE_DIRS $ENV{CPP_REPOSITORY}/sdl2_image/include)
	SET(SDL2_IMAGE_LIBRARIES $ENV{CPP_REPOSITORY}/sdl2_image/lib/x86/SDL2_image.lib)
ELSE()
	find_package(GLEW REQUIRED)
	find_package(SDL2_image REQUIRED)
ENDIF(WIN32)

MESSAGE(STATUS "")
MESSAGE(STATUS "SDL2_INCLUDE_DIR = " ${SDL2_INCLUDE_DIR})
MESSAGE(STATUS "SDL2_LIBRARY = " ${SDL2_LIBRARY})
MESSAGE(STATUS "SDL2_IMAGE_INCLUDE_DIRS = " ${SDL2_IMAGE_INCLUDE_DIRS})
MESSAGE(STATUS "SDL2_IMAGE_LIBRARIES = " ${SDL2_IMAGE_LIBRARIES})
MESSAGE(STATUS "LUA_INCLUDE_DIR = " ${LUA_INCLUDE_DIR})
MESSAGE(STATUS "LUA_LIBRARIES = " ${LUA_LIBRARIES})
MESSAGE(STATUS "Boost_INCLUDE_DIRS = " ${Boost_INCLUDE_DIRS})
MESSAGE(STATUS "Boost_LIBRARY_DIRS = " ${Boost_LIBRARY_DIRS})
MESSAGE(STATUS "OPENGL_INCLUDE_DIR = " ${OPENGL_INCLUDE_DIR})
MESSAGE(STATUS "GLM_INCLUDE_DIRS = " ${GLM_INCLUDE_DIRS})
MESSAGE(STATUS "GLEW_INCLUDE_DIR = " ${GLEW_INCLUDE_DIR})
MESSAGE(STATUS "GLEW_LIBRARIES = " ${GLEW_LIBRARIES})
MESSAGE(STATUS "OPENGL_LIBRARIES = " ${OPENGL_LIBRARIES})
MESSAGE(STATUS "")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

# Add subdirectories

IF(WIN32)
	add_subdirectory(platform/win32)
ENDIF(WIN32)

IF(APPLE)
	add_subdirectory(platform/osx)
ENDIF(APPLE)

add_subdirectory(core)
add_subdirectory(game)
add_subdirectory(editor)

