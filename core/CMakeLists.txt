project(core)

INCLUDE_DIRECTORIES(
	${core_SOURCE_DIR}/include/
)

#########################################################################################
#											                                            #
#				                    INCLUDE FILES		        	                    #
#										                                                #
#########################################################################################

FILE (GLOB INCLUDE_ROOT
	include/*.hpp
	include/*.h
)
LIST(APPEND core_SRC ${INCLUDE_ROOT})
SOURCE_GROUP("include"
  FILES
    ${INCLUDE_ROOT}
)

FILE(GLOB INCLUDE_DATA
	include/data/*.hpp
	include/data/*.h
)
LIST(APPEND core_SRC ${INCLUDE_DATA})
SOURCE_GROUP("include\\data"
  FILES
    ${INCLUDE_DATA}
)

FILE(GLOB INCLUDE_MODEL
	include/data/model/*.h
)
LIST(APPEND core_SRC ${INCLUDE_MODEL})
SOURCE_GROUP("include\\data\\model"
  FILES
    ${INCLUDE_MODEL}
)

FILE(GLOB INCLUDE_ES
	include/es/*.h
	include/es/*.hpp
)
LIST(APPEND core_SRC ${INCLUDE_ES})
SOURCE_GROUP("include\\es"
  FILES
    ${INCLUDE_ES}
)

FILE (GLOB INCLUDE_GRAPHICS
	include/graphics/*.cpp
	include/graphics/*.hpp
	include/graphics/*.h
)
LIST(APPEND core_SRC ${INCLUDE_GRAPHICS})
SOURCE_GROUP("include\\graphics"
  FILES
    ${INCLUDE_GRAPHICS}
)

FILE (GLOB INCLUDE_GRAPHICS_SHADER
	include/graphics/shader_executor/*.hpp
	include/graphics/shader_executor/*.h
)
LIST(APPEND core_SRC ${INCLUDE_GRAPHICS_SHADER})
SOURCE_GROUP("include\\graphics\\shader_executor"
  FILES
    ${INCLUDE_GRAPHICS_SHADER}
)

FILE(GLOB INCLUDE_LIBROCKET
	include/librocket/*.hpp
	include/librocket/*.h
)
LIST(APPEND core_SRC ${INCLUDE_LIBROCKET})
SOURCE_GROUP("include\\librocket"
  FILES
    ${INCLUDE_LIBROCKET}
)

FILE(GLOB INCLUDE_MATH
	include/math/*.hpp
	include/math/*.h
)
LIST(APPEND core_SRC ${INCLUDE_MATH})
SOURCE_GROUP("include\\math"
  FILES
    ${INCLUDE_MATH}
)

FILE(GLOB INCLUDE_PLATFORM
	include/platform/*.hpp
	include/platform/*.h
)
LIST(APPEND core_SRC ${INCLUDE_PLATFORM})
SOURCE_GROUP("include\\platform"
  FILES
    ${INCLUDE_PLATFORM}
)

#########################################################################################
#											                                            #
#				                    SOURCE FILES		        	                    #
#										                                                #
#########################################################################################

FILE (GLOB SRC_ROOT
	src/*.cpp                
)
LIST(APPEND core_SRC ${SRC_ROOT})
SOURCE_GROUP("src"
  FILES
    ${SRC_ROOT}
)

FILE(GLOB SRC_DATA
	src/data/*.cpp
)
LIST(APPEND core_SRC ${SRC_DATA})
SOURCE_GROUP("src\\data"
  FILES
    ${SRC_DATA}
)

FILE(GLOB SRC_MODEL
	src/data/model/*.c
)
LIST(APPEND core_SRC ${SRC_MODEL})
SOURCE_GROUP("src\\data\\model"
  FILES
    ${SRC_MODEL}
)

FILE(GLOB SRC_ES 
	src/es/*.cpp
)  
LIST(APPEND core_SRC ${SRC_ES})
SOURCE_GROUP("src\\es"
  FILES
    ${SRC_ES}
)

FILE (GLOB SRC_GRAPHICS
	src/graphics/*.cpp
)
LIST(APPEND core_SRC ${SRC_GRAPHICS})
SOURCE_GROUP("src\\graphics"
  FILES
    ${SRC_GRAPHICS}
)

FILE (GLOB SRC_GRAPHICS_SHADER
	src/graphics/shader_executor/*.cpp
)
LIST(APPEND core_SRC ${SRC_GRAPHICS_SHADER})
SOURCE_GROUP("src\\graphics\\shader_executor"
  FILES
    ${SRC_GRAPHICS_SHADER}
)

FILE(GLOB SRC_LIBROCKET
	src/librocket/*.cpp
)
LIST(APPEND core_SRC ${SRC_LIBROCKET})
SOURCE_GROUP("src\\librocket"
  FILES
    ${SRC_LIBROCKET}
)

FILE(GLOB SRC_MATH
	src/math/*.cpp
)
LIST(APPEND core_SRC ${SRC_MATH})
SOURCE_GROUP("src\\math"
  FILES
    ${SRC_MATH}
)

#########################################################################################
#										                                                #
#			                         RESOURCES    		                                #
#										                                                #
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
#											#
#				         CONFIG  				        #
#							  			        #
#########################################################################################

add_library (core ${core_SRC})
target_link_libraries(core platform ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${LUA_LIBRARIES} ${Boost_LIBRARY_DIRS} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

install(TARGETS core ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR})