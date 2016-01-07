project(platform)

INCLUDE_DIRECTORIES(
	${platform_SOURCE_DIR}/../../core/include/platform
)

FILE (GLOB SRC_ROOT
	src/*.cpp                
	src/*.hpp
)
LIST(APPEND osx_SRC ${SRC_ROOT})
SOURCE_GROUP("src"
  FILES
    ${SRC_ROOT}
)


add_library (platform ${osx_SRC})

install(TARGETS platform ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR})