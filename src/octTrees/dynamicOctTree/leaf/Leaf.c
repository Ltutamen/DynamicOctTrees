//
// Created by Kolon on 10.02.2019.
//

#include <malloc.h>
#include "Leaf.h"

Leaf* newLeafByPtr(Position pz, Voxel* data){
    Leaf* result = (Leaf*)malloc(sizeof(Leaf));
    result->nextVoxel = nullptr;
    result->pos = pz;
    result->val = data;
    result->TYPE = 0;
    return result;
}


Position getPosition(float scale, uint flag, Position pos){
    Position result;
    result.x = ( flag & 1 ) ? ( pos.x - scale ) : (pos.x + scale );
    result.y = ( flag & 2 ) ? ( pos.y - scale ) : (pos.y + scale );
    result.z = ( flag & 4 ) ? ( pos.z - scale ) : (pos.z + scale );

    return result;
}


void leafOutputConsole(Leaf* leaf){
#ifdef SAFE
    if(leaf->TYPE!=NTYPE_LEAF)return;//TODO error
#endif
    printf("\tLeaf:");
    //printf("\t depth: %i\n", leaf->parent->currentDepth);
    printf("\t pos: x:%f, y:%f, z:%f\n", leaf->pos.x, leaf->pos.y, leaf->pos.z);
    printf("\t col: r:%f, g:%f, b:%f\n", leaf->val->col.x, leaf->val->col.y, leaf->val->col.z);
}