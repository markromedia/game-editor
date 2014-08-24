project(game)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/data
	${CMAKE_CURRENT_SOURCE_DIR}/src/es
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphics
	${CMAKE_CURRENT_SOURCE_DIR}/src/librocket
	${CMAKE_CURRENT_SOURCE_DIR}/src/math
)

set(SRC_ROOT
	src/constants.cpp                
	src/game.cpp
	src/game.hpp 
	src/game_scene.hpp
	src/game_scene.cpp  
	src/logger.hpp
	src/logger.cpp      
	src/main.cpp    
	src/sdl_app.hpp  
	src/sdl_app.cpp
	src/skybox.hpp  
	src/skybox.cpp
	src/terrain.hpp
	src/terrain.cpp
)
    
set(SRC_DATA
	src/data/model_loader.cpp  
	src/data/model_loader.hpp
	src/data/model/cube.h  
	src/data/model/cube2.h  
	src/data/model/enemy.h  
	src/data/model/falcon.h  
	src/data/model/skybox.h  
	src/data/model/station.h  
	src/data/model/teapot.h  
	src/data/model/torus.h
)

set(SRC_ES 
	src/es/entity.cpp  
	src/es/entity_manager.cpp
	src/es/entity.hpp  
	src/es/entity_manager.hpp
)  
	
set (SRC_GRAPHICS
	src/graphics/camera.cpp
	src/graphics/camera.hpp
	src/graphics/color4f.cpp
	src/graphics/color4f.hpp
	src/graphics/frame.cpp
	src/graphics/frame.hpp
	src/graphics/gllogger.cpp
	src/graphics/gllogger.hpp
	src/graphics/glstate.cpp
	src/graphics/glstate.hpp
	src/graphics/opengl.h
	src/graphics/quad.cpp
	src/graphics/quad.hpp
	src/graphics/render_op_manager.cpp
	src/graphics/render_op_manager.hpp
	src/graphics/render_operation.cpp
	src/graphics/render_operation.hpp
	src/graphics/renderexecutor.hpp
	src/graphics/rendexec_draw_model.cpp
	src/graphics/rendexec_draw_model.hpp
	src/graphics/rendexec_draw_skybox.cpp
	src/graphics/rendexec_draw_skybox.hpp
	src/graphics/rendexec_draw_terrain.cpp
	src/graphics/rendexec_draw_terrain.hpp
	src/graphics/rendexec_draw_texture.cpp
	src/graphics/rendexec_draw_texture.hpp
	src/graphics/rendexec_draw_wireframe.cpp
	src/graphics/rendexec_draw_wireframe.hpp
	src/graphics/shader_manager.cpp
	src/graphics/shader_manager.hpp
	src/graphics/shader_object.cpp
	src/graphics/shader_object.hpp
	src/graphics/texture.cpp
	src/graphics/texture.hpp
	src/graphics/texture_manager.cpp
	src/graphics/texture_manager.hpp
	src/graphics/vertex_buffer.cpp
	src/graphics/vertex_buffer.hpp
	src/graphics/vertex_buffer_manager.cpp
	src/graphics/vertex_buffer_manager.hpp
	src/graphics/vertex_data.cpp
	src/graphics/vertex_data.hpp
)

set(SRC_LIBROCKET
	src/librocket/librocket_renderer.cpp  
	src/librocket/librocket_renderer.hpp  
	src/librocket/librocket_system.cpp  
	src/librocket/librocket_system.hpp
)

set(SRC_MATH
	src/math/matrix3.cpp  
	src/math/matrix3.hpp  
	src/math/matrix4.cpp  
	src/math/matrix4.hpp  
	src/math/vector4.cpp  
	src/math/vector4.hpp
)

set(core_SRC
	${SRC_ROOT}
	${SRC_DATA}
	${SRC_ES}
	${SRC_GRAPHICS}
	${SRC_LIBROCKET}
	${SRC_MATH}
)	

MESSAGE(STATUS ${core_SRC})



add_executable(game ${core_SRC})
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${LUA_LIBRARIES} ${Boost_LIBRARY_DIRS} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
install(TARGETS game RUNTIME DESTINATION ${BIN_DIR})