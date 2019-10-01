//
// Created by Kolon on 10.02.2019.
//

#include <malloc.h>
#include <stdlib.h>
#include "Branch.h"
#include "../octtree/OctTree.h"


Branch* newBranchByPtr(Branch* par, uint flag){
    Branch* result = (Branch*)malloc(sizeof(Branch));
    result->TYPE = NTYPE_BRANCH;

    result->pos = getPosition(par->maxScale/2, flag, par->pos);

    for(int i =0 ; i<8; i++)result->children[i] = nullptr;

    result->currentDepth = par->currentDepth+1;
    result->parent = par;
    return result;
}


Vector3f* writeVertexArr(Branch* br, Vector3f* pointer){
#ifdef  SAFE
    if(br==nullptr)return pointer;
    if(pointer==nullptr){
        puts("\nBranch.c writeVertexArray error");
        exit(12);
    }
#endif
    for(uint i=0 ; i<8 ; i++){
        if(br->children[i]==nullptr){}
        else if(br->children[i]->TYPE==NTYPE_BRANCH){
            pointer = writeVertexArr((Branch*)br->children[i], pointer);
        }
        else if(br->children[i]->TYPE==NTYPE_LEAF){
            *pointer = br->children[i]->pos;
            pointer++;
        }
        else if(br->children[i]->TYPE==NTYPE_OCTTREE){
            pointer = writeVertexArr( ((OctTree*)br->children[i])->_root, pointer);
        }
    }
    return pointer;
}



void branchOutputConsole(Branch* branch){
#ifdef SAFE
    if(branch->TYPE!=NTYPE_BRANCH)return;;
#endif
    for(uint i=0 ; i<8 ; i++){
        if(branch->children[i]){
            switch (branch->children[i]->TYPE){
                case NTYPE_BRANCH:{
                    branchOutputConsole((Branch*)branch->children[i]);
                    break;
                }
                case NTYPE_LEAF:{
                    leafOutputConsole((Leaf*)branch->children[i]);
                    break;
                }
                case NTYPE_OCTTREE:{
                    octTreeOutputConsole((OctTree*)branch->children[i]);
                    break;
                }
                default:{
                    printf("ERROR");
                }

            }
        }
    }
}
