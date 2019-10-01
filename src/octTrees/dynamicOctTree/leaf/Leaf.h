//
// Created by Kolon on 10.02.2019.
//

#ifndef DYNAMICOCTTREE_CI_LEAF_H
#define DYNAMICOCTTREE_CI_LEAF_H

#include "Node.h"
#include "voxel/Voxel.h"
#include "../branch/Branch.h"

typedef struct Leaf{
    NTYPE TYPE;     // first member -  type
    Position pos;   // second member - position
    //
    Voxel* val;
    Branch* parent;
    struct Leaf* nextVoxel;     //Leaf points to another Leaf, to create a polygoon, all leavs create cycle
    //uint32 currentDepth; //use depth of the parentbranch
}Leaf;

Leaf* newLeafByPtr(Position pz, Voxel* data);
Position getPosition(float scale, uint flag, Position pos);

void leafOutputConsole(Leaf* leaf);

#endif //DYNAMICOCTTREE_CI_LEAF_H
