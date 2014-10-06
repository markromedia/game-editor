project(platform)

INCLUDE_DIRECTORIES(
	${platform_SOURCE_DIR}/../../core/src/platform
)

FILE (GLOB SRC_ROOT
	src/*.cpp                
	src/*.hpp
)
LIST(APPEND linux_SRC ${SRC_ROOT})
SOURCE_GROUP("src"
  FILES
    ${SRC_ROOT}
)


add_library (platform ${linux_SRC})

install(TARGETS platform ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR})