//
// Created by Kolon on 10.02.2019.
//

#ifndef DYNAMICOCTTREE_CI_BRANCH_H
#define DYNAMICOCTTREE_CI_BRANCH_H

#include "../leaf/Node.h"
#include "../branch/Branch.h"
#include "../../../game/engine/mathematics/vectors/Vectors.h"

typedef struct Branch{
    NTYPE TYPE;     //Type is first< as it should be
    Position pos;   //position is second, as it should be
    //
    uint32 currentDepth;
    float maxScale;
    struct Branch* parent;
    Node* children[8];      //static poiter array
}Branch;

Branch* newBranchByPtr(Branch* par, uint flag);


//output func
void branchOutputConsole(Branch* branch);

Vector3f* writeVertexArr(Branch* br, Vector3f* pointer);

#endif //DYNAMICOCTTREE_CI_BRANCH_H
