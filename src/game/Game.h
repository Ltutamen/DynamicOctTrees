//
// Created by axiom on 4/10/19.
//

#ifndef DYNAMICOCTTREE_CI_GAME_H
#define DYNAMICOCTTREE_CI_GAME_H

#include <GLFW/glfw3.h>
#include "../octTrees/dynamicOctTree/octtree/OctTree.h"
#include "../graphics/screen/Window/Window.h"
#include "gameProperties/GameProperties.h"
#include "player/Player.h"


typedef struct {
    GLboolean isRunning;
    OctTree* world;
    Player player;
    GLFWwindow* window;
    Window winProperties;
    GameProperties gameProps;
    GLint matrixID;

    GLuint VertexArrayID;
    GLuint vertexBuffer;

}Game;

Game newGameOpenGlInit(OctTree* w);
void gameLoop(Game game);


#endif //DYNAMICOCTTREE_CI_GAME_H
