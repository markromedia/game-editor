project(platform)

INCLUDE_DIRECTORIES(
	${core_SOURCE_DIR}/include/platform
)

FILE (GLOB SRC_ROOT
	src/*.cpp                
	src/*.hpp
)
LIST(APPEND win32_SRC ${SRC_ROOT})
SOURCE_GROUP("src"
  FILES
    ${SRC_ROOT}
)


add_library (platform ${win32_SRC})

install(TARGETS platform ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR})