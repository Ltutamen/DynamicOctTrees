//
// Created by axiom on 5/1/19.
//

#include <malloc.h>
#include "Player.h"


Player* newPlayer(){
    Player* result = (Player*)malloc(sizeof(Player));
    result->pos = *newVector3f(0.0f ,0.0f, 0.0f );
    result->view = *newVector3f(0.0f ,0.0f, 0.0f );
    result->horizontalAngle = 3.14f;
    result->vertivalAngle = 0.0f;
    result->initialFOV = 90.0f;
    result->speed = 3.0f;
    result->mouseSpeed = 0.005f;
    return result;
}