cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME VINCERE)
project(DynamicOctTree_Ci)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_CLANG_TIDY="--x86-asm-syntax=intel;-masm=intel")


find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

add_executable(DynamicOctTree_Ci main.c
        src/game/engine/mathematics/vectors/Vectors.h
        src/octTrees/dynamicOctTree/octtree/OctTree.c
        src/octTrees/dynamicOctTree/octtree/OctTree.h
        src/octTrees/dynamicOctTree/branch/Branch.c
        src/octTrees/dynamicOctTree/branch/Branch.h
        src/octTrees/dynamicOctTree/leaf/Leaf.c
        src/octTrees/dynamicOctTree/leaf/Leaf.h
        src/octTrees/dynamicOctTree/leaf/voxel/Voxel.h
        src/octTrees/dynamicOctTree/leaf/Node.h
        src/game/engine/mathematics/vectors/Vectors.c
        src/octTrees/dynamicOctTree/leaf/voxel/Voxel.c
        src/octTrees/dynamicOctTree/octtree/files/objFile.c
        src/octTrees/dynamicOctTree/octtree/files/objFile.h
        src/graphics/screen/Window/Window.c
        src/graphics/screen/Window/Window.h
        src/game/Game.c
        src/game/Game.h
        src/graphics/shaders/Shader.c
        src/graphics/shaders/Shader.h
        src/graphics/buffer/Buffer.c
        src/graphics/buffer/Buffer.h
        src/game/player/Player.c
        src/game/player/Player.h
        src/game/engine/mathematics/matrices/Matrics.c
        src/game/engine/mathematics/matrices/Matrics.h
        src/game/engine/mathematics/operations/Sqrt.c
        src/game/engine/mathematics/operations/Sqrt.h
#        src/logging/ErrorLogging.c src/logging/ErrorLogging.h
        src/game/gameProperties/GameProperties.c
        src/game/gameProperties/GameProperties.h
        test/MathTest.c
        test/MathTest.h
        )

#target_include_directories(DynamicOctTree_Ci ${OPENGL_LIBRARIES})

target_link_libraries(DynamicOctTree_Ci m)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} GL)