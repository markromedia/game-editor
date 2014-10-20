project(editor)

MESSAGE(STATUS "***************************************************")
MESSAGE(STATUS "*                  Editor Config                  *")
MESSAGE(STATUS "***************************************************")


#for linux, need to fix the path for awesomium. fix this
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    MESSAGE(STATUS "Awesomium path is going to be hardcoded")
    SET(AWESOMIUM_INCLUDE_DIR /home/mudit/applications/awesomium/awesomium_v1.7.4_sdk_linux64/include)
    SET(AWESOMIUM_LIBRARY /home/mudit/applications/awesomium/awesomium_v1.7.4_sdk_linux64/bin/libawesomium-1-7.so.4.0)
ElSE()
    find_package(Awesomium REQUIRED)
ENDIF()


MESSAGE(STATUS "AWESOMIUM_INCLUDE_DIR = " ${AWESOMIUM_INCLUDE_DIR})
MESSAGE(STATUS "AWESOMIUM_LIBRARY = " ${AWESOMIUM_LIBRARY})

include_directories(${AWESOMIUM_INCLUDE_DIR})


#########################################################################################
#																						#
#  			CORE LIBRARY INCLUDES										#
#						  															    #
#########################################################################################

INCLUDE_DIRECTORIES(
	${core_SOURCE_DIR}/include/
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
FILE(GLOB RES_ROOT
	resources/*.*
)
LIST(APPEND editor_SRC ${RES_ROOT})
SOURCE_GROUP("resources"
  FILES
    ${RES_ROOT}
)

FILE(GLOB RES_EDITOR
	resources/editor/*.*
)
LIST(APPEND editor_SRC ${RES_EDITOR})
SOURCE_GROUP("resources\\editor"
  FILES
    ${RES_EDITOR}
)

FILE(GLOB RES_EDITOR_UI
	resources/editor/ui/*.*
)
LIST(APPEND editor_SRC ${RES_EDITOR_UI})
SOURCE_GROUP("resources\\editor\\ui"
  FILES
    ${RES_EDITOR_UI}
)

FILE(GLOB RES_EDITOR_HTML
	resources/editor/ui/html/*.*
)
LIST(APPEND editor_SRC ${RES_EDITOR_HTML})
SOURCE_GROUP("resources\\editor\\ui\\html"
  FILES
    ${RES_EDITOR_HTML}
)



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

add_custom_command(TARGET editor PRE_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${editor_SOURCE_DIR}/resources $<TARGET_FILE_DIR:editor>/resources)
	

#copy dll's
IF (WIN32)
add_custom_command(TARGET editor PRE_BUILD  
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/../platform/win32/dll $<TARGET_FILE_DIR:editor>)

add_custom_command(TARGET editor PRE_BUILD  
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					$ENV{AWE_DIR}/build/bin $<TARGET_FILE_DIR:editor>)
ENDIF(WIN32)

install(TARGETS editor RUNTIME DESTINATION ${BIN_DIR})

MESSAGE(STATUS "")