cmake_minimum_required(VERSION 3.10)
project(GraphicsEngine-OpenGL)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS1 "Libraries/include/GE/*.h")
file(GLOB_RECURSE HEADERS2 "Libraries/include/GE/Components/*.h")
file(GLOB_RECURSE HEADERS3 "Libraries/include/GE/Entity/*.h")
file(GLOB_RECURSE HEADERS4 "Libraries/include/GE/HelperClasses/*.h")

add_library(
	GraphicsEngine-OpenGL STATIC ${SOURCES} ${HEADERS1} ${HEADERS2} ${HEADERS3} ${HEADERS4} src/glad.c
)

target_include_directories(GraphicsEngine-OpenGL PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/include)

target_link_libraries(GraphicsEngine-OpenGL PRIVATE ${PROJECT_SOURCE_DIR}/Libraries/lib/glfw3.lib)
target_link_libraries(GraphicsEngine-OpenGL PRIVATE ${PROJECT_SOURCE_DIR}/Libraries/lib/assimp-vc143-mt.lib)