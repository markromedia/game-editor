project(core)

#########################################################################################
#											                                            #
#				                      SOURCE FILES					                    #
#											                                            #
#########################################################################################

#include_directories(
#	${CMAKE_CURRENT_SOURCE_DIR}/src
#	${CMAKE_CURRENT_SOURCE_DIR}/src/data
#	${CMAKE_CURRENT_SOURCE_DIR}/src/data/model
#	${CMAKE_CURRENT_SOURCE_DIR}/src/es
#	${CMAKE_CURRENT_SOURCE_DIR}/src/graphics
#	${CMAKE_CURRENT_SOURCE_DIR}/src/librocket
#	${CMAKE_CURRENT_SOURCE_DIR}/src/math
#)

FILE (GLOB SRC_ROOT
	src/*.cpp                
	src/*.hpp
)
LIST(APPEND core_SRC ${SRC_ROOT})
SOURCE_GROUP("src"
  FILES
    ${SRC_ROOT}
)

FILE(GLOB SRC_DATA
	src/data/*.cpp
	src/data/*.hpp
)
LIST(APPEND core_SRC ${SRC_DATA})
SOURCE_GROUP("src\\data"
  FILES
    ${SRC_DATA}
)

FILE(GLOB SRC_MODEL
	src/data/model/*.h
	src/data/model/*.c
)
LIST(APPEND core_SRC ${SRC_MODEL})
SOURCE_GROUP("src\\data\\model"
  FILES
    ${SRC_MODEL}
)

FILE(GLOB SRC_ES 
	src/es/*.hpp
	src/es/*.cpp
)  
LIST(APPEND core_SRC ${SRC_ES})
SOURCE_GROUP("src\\es"
  FILES
    ${SRC_ES}
)

FILE (GLOB SRC_GRAPHICS
	src/graphics/*.cpp
	src/graphics/*.hpp
)
LIST(APPEND core_SRC ${SRC_GRAPHICS})
SOURCE_GROUP("src\\graphics"
  FILES
    ${SRC_GRAPHICS}
)

FILE(GLOB SRC_LIBROCKET
	src/librocket/*.cpp
	src/librocket/*.hpp
)
LIST(APPEND core_SRC ${SRC_LIBROCKET})
SOURCE_GROUP("src\\librocket"
  FILES
    ${SRC_LIBROCKET}
)

FILE(GLOB SRC_MATH
	src/math/*.cpp
	src/math/*.hpp
)
LIST(APPEND core_SRC ${SRC_MATH})
SOURCE_GROUP("src\\math"
  FILES
    ${SRC_MATH}
)
	

#########################################################################################
#											                                            #
#				                     RESOURCES    		                    			#
#										                                            	#
#########################################################################################


FILE(GLOB RES_ROOT
	resources/*.*
)
LIST(APPEND core_SRC ${RES_ROOT})
SOURCE_GROUP("resources"
  FILES
    ${RES_ROOT}
)

FILE(GLOB RES_ROCKET
	resources/rocket/*.*
)
LIST(APPEND core_SRC ${RES_ROCKET})
SOURCE_GROUP("resources\\rocket"
  FILES
    ${RES_ROCKET}
)

FILE(GLOB RES_ROCKET_ASSETS
	resources/rocket/assets/*.*
)
LIST(APPEND core_SRC ${RES_ROCKET_ASSETS})
SOURCE_GROUP("resources\\rocket\\assets"
  FILES
    ${RES_ROCKET_ASSETS}
)

FILE(GLOB RES_SHADER
	resources/shader/*.*
)
LIST(APPEND core_SRC ${RES_SHADER})
SOURCE_GROUP("resources\\shader"
  FILES
    ${RES_SHADER}
)

FILE(GLOB RES_SKYBOX
	resources/skybox/*.*
)
LIST(APPEND core_SRC ${RES_SKYBOX})
SOURCE_GROUP("resources\\skybox"
  FILES
    ${RES_SKYBOX}
)



#########################################################################################
#											                                            #
#				                      CONFIG      					                    #
#											                                            #
#########################################################################################

add_executable(game ${core_SRC})
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${LUA_LIBRARIES} ${Boost_LIBRARY_DIRS} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

#copy resources
add_custom_command(TARGET game POST_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:game>/resources)

#copy dll
IF (WIN32)
add_custom_command(TARGET game POST_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/../win32/dll $<TARGET_FILE_DIR:game>)

					MESSAGE(STATUS "GAME SOURCE " ${CMAKE_SOURCE_DIR})
ENDIF(WIN32)

install(TARGETS game RUNTIME DESTINATION ${BIN_DIR})