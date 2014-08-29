project(game)

#########################################################################################
#											#
#				      CORE LIBRARY INCLUDES				#
#										        #
#########################################################################################

INCLUDE_DIRECTORIES(
	${core_SOURCE_DIR}/src/
	${core_SOURCE_DIR}/src/data
	${core_SOURCE_DIR}/src/data/model
	${core_SOURCE_DIR}/src/es
	${core_SOURCE_DIR}/src/graphics
	${core_SOURCE_DIR}/src/librocket
	${core_SOURCE_DIR}/src/math
	${core_SOURCE_DIR}/src/platform
)

#########################################################################################
#											#
#				      SOURCE FILES		        		#
#										        #
#########################################################################################
FILE (GLOB SRC_ROOT
	src/*.cpp                
	src/*.hpp
    src/*.h
)
LIST(APPEND game_SRC ${SRC_ROOT})
SOURCE_GROUP("src"
  FILES
    ${SRC_ROOT}
)


#########################################################################################
#										        #
#			               RESOURCES    		                        #
#										        #
#########################################################################################
  FILE(GLOB RES_ROOT
	resources/*.*
)
LIST(APPEND core_SRC ${RES_ROOT})
SOURCE_GROUP("resources"
  FILES
    ${RES_ROOT}
)



#########################################################################################
#											#
#				         CONFIG  				        #
#							  			        #
#########################################################################################

add_executable(game ${game_SRC})
add_library (game_lib ${game_SRC})

target_link_libraries(game core)

#copy core projects resources
add_custom_command(TARGET game PRE_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${core_SOURCE_DIR}/resources $<TARGET_FILE_DIR:game>/resources)

#copy dll's
IF (WIN32)
add_custom_command(TARGET game PRE_BUILD  
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/../platform/win32/dll $<TARGET_FILE_DIR:game>)
ENDIF(WIN32)

install(TARGETS game RUNTIME DESTINATION ${BIN_DIR})
install(TARGETS game_lib ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR})