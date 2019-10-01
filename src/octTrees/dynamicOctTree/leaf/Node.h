//
// Created by Kolon on 10.02.2019.
//

#ifndef DYNAMICOCTTREE_CI_NODE_H
#define DYNAMICOCTTREE_CI_NODE_H

#include "../../../game/engine/mathematics/vectors/Vectors.h"


enum NTYPE_VAL { NTYPE_NODE=-1, NTYPE_LEAF=0, NTYPE_BRANCH=1, NTYPE_OCTTREE=2 };
// not only this shovws difference between node types, but also sets priority, bigger number = bigger priority
/*
NTYPE NTYPE_NODE =     -1;
NTYPE NTYPE_LEAF =      0;
NTYPE NTYPE_BRANCH =    1;
NTYPE NTYPE_OCTTREE =   2;
*/


typedef int32 NTYPE;

typedef struct {
    NTYPE TYPE; //NTYPE can be checked correctly even from vong type pointer
    Position pos;   //position member exists everyvhere and
    //
}Node;


#endif //DYNAMICOCTTREE_CI_NODE_H
