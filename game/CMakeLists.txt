project(game)

file(GLOB_RECURSE game_SRC
    "*.h"
    "*.hpp"
    "*.cpp"
)

add_executable(game ${game_SRC})
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${LUA_LIBRARIES} ${Boost_LIBRARY_DIRS} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
install(TARGETS game RUNTIME DESTINATION ${BIN_DIR})