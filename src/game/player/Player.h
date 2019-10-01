//
// Created by axiom on 5/1/19.
//

#ifndef DYNAMICOCTTREE_CI_PLAYER_H
#define DYNAMICOCTTREE_CI_PLAYER_H


#include "../engine/mathematics/vectors/Vectors.h"

typedef struct {
    Vector3f pos;

    Vector3f view;
    float horizontalAngle;
    float vertivalAngle;
    float initialFOV;
    float speed;
    float mouseSpeed;

}Player;

Player* newPlayer();

#endif //DYNAMICOCTTREE_CI_PLAYER_H
