cmake_minimum_required(VERSION 3.0.1)

if (WIN32)
	Message(STATUS "***************************************************************************")
	Message(STATUS "*                           WINDOWS USERS!!! READ THIS                    *")
	Message(STATUS "*  Your environment variables must be correct for cmake to work           *")
	Message(STATUS "*              You must run CMake as an administrator                     *")
	Message(STATUS "***************************************************************************\n\n")
ENDIF()


project(Flight)

MESSAGE(STATUS "***************************************************")
MESSAGE(STATUS "*                  Main Config                    *")
MESSAGE(STATUS "***************************************************")

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
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

# boost configuration
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_DEBUG TRUE) 

#if windows, manually fix some dependencies
IF(WIN32)
	SET(GLEW_INCLUDE_DIR $ENV{CPP_REPOSITORY}/glew/include)
	SET(GLEW_LIBRARIES $ENV{CPP_REPOSITORY}/glew/lib/glew32s.lib)

	SET(SDL2_IMAGE_INCLUDE_DIRS $ENV{CPP_REPOSITORY}/sdl2_image/include)
	SET(SDL2_IMAGE_LIBRARIES $ENV{CPP_REPOSITORY}/sdl2_image/lib/x86/SDL2_image.lib)
	
	set(BOOST_ROOT $ENV{CPP_REPOSITORY}/boost_1_56_0)
	set(Boost_COMPILER -vc110)
	find_package(Boost REQUIRED COMPONENTS chrono date_time system thread)
ELSE()
	find_package(Boost REQUIRED COMPONENTS chrono date_time system thread)
	find_package(GLEW REQUIRED)
	find_package(SDL2_image REQUIRED)
ENDIF(WIN32)

#for linux, need to fix the path for awesomium. fix this
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    MESSAGE(STATUS "Awesomium path is going to be hardcoded")
    SET(AWESOMIUM_ROOT "/home/mudit/applications/awesomium_v1.7.4_sdk_linux32")
ENDIF()

#MESSAGE(STATUS "")
MESSAGE(STATUS "SDL2_INCLUDE_DIR = " ${SDL2_INCLUDE_DIR})
MESSAGE(STATUS "SDL2_LIBRARY = " ${SDL2_LIBRARY})
MESSAGE(STATUS "SDL2_IMAGE_INCLUDE_DIRS = " ${SDL2_IMAGE_INCLUDE_DIRS})
MESSAGE(STATUS "SDL2_IMAGE_LIBRARIES = " ${SDL2_IMAGE_LIBRARIES})
MESSAGE(STATUS "LUA_INCLUDE_DIR = " ${LUA_INCLUDE_DIR})
MESSAGE(STATUS "LUA_LIBRARIES = " ${LUA_LIBRARIES})
MESSAGE(STATUS "Boost_INCLUDE_DIRS = " ${Boost_INCLUDE_DIRS})
MESSAGE(STATUS "Boost Libaries")
MESSAGE(STATUS "    Boost_CHRONO_LIBRARY = " ${Boost_CHRONO_LIBRARY})
MESSAGE(STATUS "    Boost_DATE_TIME_LIBRARY = " ${Boost_DATE_TIME_LIBRARY})
MESSAGE(STATUS "    Boost_SYSTEM_LIBRARY = " ${Boost_SYSTEM_LIBRARY})
MESSAGE(STATUS "    Boost_THREAD_LIBRARY = " ${Boost_THREAD_LIBRARY})
MESSAGE(STATUS "OPENGL_INCLUDE_DIR = " ${OPENGL_INCLUDE_DIR})
MESSAGE(STATUS "GLM_INCLUDE_DIRS = " ${GLM_INCLUDE_DIRS})
MESSAGE(STATUS "GLEW_INCLUDE_DIR = " ${GLEW_INCLUDE_DIR})
MESSAGE(STATUS "")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

# Add subdirectories

IF(WIN32)
	add_subdirectory(platform/win32)
ENDIF(WIN32)

IF(APPLE)
	add_subdirectory(platform/osx)
ENDIF(APPLE)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_subdirectory(platform/linux)
ENDIF()

add_subdirectory(core)
add_subdirectory(game)
add_subdirectory(editor)

