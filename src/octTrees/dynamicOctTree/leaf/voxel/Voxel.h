//
// Created by Kolon on 10.02.2019.
//

#ifndef DYNAMICOCTTREE_CI_VOXEL_H
#define DYNAMICOCTTREE_CI_VOXEL_H

#include "../../../../game/engine/mathematics/vectors/Vectors.h"

typedef struct {
    Color col;
    int mod;    //additional data storage
    void* ptr;  //ptr to possible content
} Voxel;


Voxel* newVoxel(Color c, int m);

#endif //DYNAMICOCTTREE_CI_VOXEL_H
