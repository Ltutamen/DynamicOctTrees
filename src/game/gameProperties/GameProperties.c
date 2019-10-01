//
// Created by axiom on 6/6/19.
//

#include <GLFW/glfw3.h>
#include "GameProperties.h"

GameProperties newGamePreoprties(){
    GameProperties result;
    result.lastCycleTime = glfwGetTime();
    return result;
}