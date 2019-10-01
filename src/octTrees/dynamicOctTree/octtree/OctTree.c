//
// Created by Kolon on 10.02.2019.
//
#include <malloc.h>

#include "OctTree.h"
#include "../leaf/Node.h"
#include "../leaf/Leaf.h"
#include "../branch/Branch.h"


Branch* newRootBranch(OctTree* parent);     //root branch cannot receive Branch as a parent

inline int isInBound(Position pos, Position octTreeRoot, double maxCoord);
inline uint getFlag(Position pos, Position center);


Branch* getSuitableBranch(Branch* root, Position* pos);


//AKA constructor
OctTree* newOctTree(Position pos, float mcord, Branch* par){
    OctTree* result = (OctTree*)malloc(sizeof(OctTree));
    result->TYPE = NTYPE_OCTTREE;
    result->parent = par;

    result->rootPos = pos;
    result->maxCoordinate = mcord;
    result->elementsCount = 0;

    result->_root = newRootBranch(result);

    return result;
}


Branch* newRootBranch(OctTree* parent){
    Branch* result = (Branch*)malloc(sizeof(Branch));

    result->TYPE = NTYPE_BRANCH;
    result->pos = parent->rootPos;

    for(int i =0 ; i<8; i++)result->children[i] = nullptr;

    result->currentDepth = 0;
    result->maxScale = parent->maxCoordinate;
    result->parent = (Branch*)parent;
    return result;
}


void addNodeToOcttree(Node* node, OctTree* tree){

    Branch* temp = getSuitableBranch(tree->_root, &node->pos);
    uint flag = getFlag(node->pos, temp->pos);

    switch (node->TYPE) {
        case NTYPE_OCTTREE : {
            tree->elementsCount += ((OctTree *) node)->elementsCount;
            ((OctTree *) node)->parent = temp;
            temp->children[flag] = node;
            break;
        }
        case NTYPE_LEAF : {
            tree->elementsCount += 1;
            //((Leaf*)node)->currentDepth = temp->currentDepth;
            temp->children[flag] = node;
            break;
        }
        case NTYPE_BRANCH : {
#ifdef PRESIZE
            for(uint i=0; i<8 ; i++){
                if(branch->children[i]!=nullptr)tree->elementsCount +=1;
            }
#endif
#ifdef ROUGH
            tree->elementsCount += 8;
#endif
            ((Branch *) node)->currentDepth = temp->currentDepth + 1;
            temp->children[flag] = node;
            break;
        }
    }
#ifdef PRESIZE
        case NTYPE_NODE : {
            printf("\nError addind node to branch");
            break;
        }
        default : {
            printf("\nError addind node to branch, default statement should never be called");
        }
    }
#endif
}


void addNodeToBranch(Branch* branch, Node* node) {
    uint flag = getFlag(branch->pos, node->pos);
    branch = getSuitableBranch(branch, &node->pos);

    branch->children[flag] = node;

}


void addMeshToOcttree(OctTree* tree, float* positionMesh, float* colorMesh, uint meshSize) { //size means amount of 3-int blocks
#ifdef SAFE
    if (!tree || !positionMesh || !colorMesh) return;
#endif
    for (uint i = 0; i < meshSize; i++) {
        Leaf *temp = newLeafByPtr(*newVector3f(positionMesh[0], positionMesh[1], positionMesh[2]),
                                  newVoxel(*newVector3f(colorMesh[0], colorMesh[1], colorMesh[2]), 1));     //position, Voxel, parent, depth
        addNodeToOcttree((Node*)temp, tree);
        positionMesh += 3;
        colorMesh += 3;
    }
}


void addPolygonToOcttree(OctTree* tree, float* posMesh){         //meshSize = 9 * meshSize points
    Leaf* tempa= newLeafByPtr( *newVector3f(posMesh[0], posMesh[1], posMesh[2]), newVoxel(*newVector3f(0.5f, 0.5f, 0.5f), 0));
    Leaf* tempb= newLeafByPtr( *newVector3f(posMesh[3], posMesh[4], posMesh[5]), newVoxel(*newVector3f(0.5f, 0.5f, 0.5f), 0));
    Leaf* tempc= newLeafByPtr( *newVector3f(posMesh[6], posMesh[7], posMesh[8]), newVoxel(*newVector3f(0.5f, 0.5f, 0.5f), 0));

    tempa->nextVoxel = tempb;
    tempb->nextVoxel = tempc;
    tempc->nextVoxel = tempa;

    addNodeToOcttree((Node*)tempa, tree);
    addNodeToOcttree((Node*)tempb, tree);
    addNodeToOcttree((Node*)tempc, tree);

}


//MISC
int isInBound(Position pos, Position octTreeRoot, double maxCoord){
    if( pos.x > octTreeRoot.x+maxCoord || pos.x < octTreeRoot.x-maxCoord ) return 0;
    if( pos.y > octTreeRoot.y+maxCoord || pos.y < octTreeRoot.y-maxCoord ) return 0;
    if( pos.z > octTreeRoot.z+maxCoord || pos.z < octTreeRoot.z-maxCoord ) return 0;
    return 1;
}


uint getFlag(Position pos, Position center){
    uint result = 0;
    if( pos.x>center.x )result = 1;
    if( pos.y>center.y )result +=2;
    if( pos.z>center.z )result +=4;
    return result;
}


int getPriority(Node* a, Node* b){     //some node* are in fact branches, and should be processed first
    return ((b->TYPE) - (a->TYPE));
}

//Returns pointer to branch, that has free space
//on the @flag pointed space
//reorganises tree in needed
Branch* getSuitableBranch(Branch* root, Position* pos){
    uint flag = getFlag(*pos, root->pos);
    while(root->children[flag] && root->children[flag]->TYPE==NTYPE_BRANCH){
        root = (Branch*)root->children[flag];
        flag = getFlag(*pos, root->pos);
    }

    if(root->children[flag]==nullptr){
        return root;
    }

    Node* temp = root->children[flag];
    root->children[flag] = (Node*)newBranchByPtr(root, flag);
    root = (Branch*)root->children[flag];
    addNodeToBranch(root, temp);
    return getSuitableBranch(root, pos);  //recursively call same func, retun only on first return statement

}


void octTreeOutputConsole(OctTree* tree){
    printf(" Tree output:\n");
    printf("  max coord: %f\n", tree->maxCoordinate);
    printf("  elements count: %llu\n", tree->elementsCount);
    Branch* r = tree->_root;
    for(uint i = 0 ; i<8 ; i++){
        if(r->children[i]){
            switch (r->children[i]->TYPE) {
                case NTYPE_BRANCH:{
                    branchOutputConsole((Branch*)r->children[i]);
                    break;
                }
                case NTYPE_LEAF:{
                    leafOutputConsole((Leaf*)r->children[i]);
                    break;
                }
                case NTYPE_OCTTREE:{
                    octTreeOutputConsole((OctTree*)r->children[i]);
                    break;
                }
                default:{
                    printf("ERROR"); //TODO error
                }
            }
        }
    }
}


const Vector3f* octTreeGetVertexArray(OctTree* tree){
    const Vector3f* result = (const Vector3f*)malloc(sizeof(Vector3f) * tree->elementsCount );        //3 floats for every point
    writeVertexArr(tree->_root, result);
    return result;

}


