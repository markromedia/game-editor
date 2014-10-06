project(editor)

MESSAGE(STATUS "***************************************************")
MESSAGE(STATUS "*                  Editor Config                  *")
MESSAGE(STATUS "***************************************************")

find_package(Awesomium REQUIRED)

MESSAGE(STATUS "AWESOMIUM_INCLUDE_DIR = " ${AWESOMIUM_INCLUDE_DIR})
MESSAGE(STATUS "AWESOMIUM_LIBRARY = " ${AWESOMIUM_LIBRARY})

include_directories(${AWESOMIUM_INCLUDE_DIR})


#########################################################################################
#																						#
#  			CORE LIBRARY INCLUDES										#
#						  															    #
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
#																						#
#				      GAME LIBRARY INCLUDES												#
#																						#
#########################################################################################

INCLUDE_DIRECTORIES(
	${game_SOURCE_DIR}/src/
)


#########################################################################################
#											#
#				      SOURCE FILES		        		#
#										        #
#########################################################################################
FILE (GLOB SRC_ROOT
	src/*.cpp                
	src/*.hpp
)
LIST(APPEND editor_SRC ${SRC_ROOT})
SOURCE_GROUP("src"
  FILES
    ${SRC_ROOT}
)


#########################################################################################
#										        #
#			               RESOURCES    		                        #
#										        #
#########################################################################################


#########################################################################################
#											#
#				         CONFIG  				        #
#							  			        #
#########################################################################################

add_executable(editor ${editor_SRC})

target_link_libraries(editor core game_lib ${AWESOMIUM_LIBRARY})

#copy core projects resources
add_custom_command(TARGET editor PRE_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${core_SOURCE_DIR}/resources $<TARGET_FILE_DIR:editor>/resources)

#copy dll's
IF (WIN32)
add_custom_command(TARGET editor PRE_BUILD  
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/../platform/win32/dll $<TARGET_FILE_DIR:editor>)

add_custom_command(TARGET editor PRE_BUILD  
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					$ENV{AWE_DIR}/build/bin/packed $<TARGET_FILE_DIR:editor>)
ENDIF(WIN32)

install(TARGETS editor RUNTIME DESTINATION ${BIN_DIR})

MESSAGE(STATUS "")