//
// Created by axiom on 3/29/19.
//

#include <malloc.h>
#include "Voxel.h"

Voxel* newVoxel(Color c, int m){
    Voxel* result = (Voxel*)malloc(sizeof(Voxel));
    result->col = c;
    result->mod = m;
    return result;
}