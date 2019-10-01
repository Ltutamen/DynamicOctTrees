//
// Created by Kolon on 10.02.2019.
//

#ifndef DYNAMICOCTTREE_CI_OCTTREE_H
#define DYNAMICOCTTREE_CI_OCTTREE_H

#define ROUGH
#ifndef ROUGH
 #define PRESIZE
#endif

#define SAFE
#ifndef SAFE
 #define UNSAFE
#endif


#include "../branch/Branch.h"
#include "../leaf/voxel/Voxel.h"
#include "../leaf/Leaf.h"


typedef struct {
    NTYPE TYPE;         //describes the struct type, used to work with Void pointers
    Position rootPos;
    //
    Branch* _root;
    Branch* parent;
    float maxCoordinate;
    ullong elementsCount;       //vital for perfomance, when voxel mech is dynamicly allocated, allocate this*1.1 size array once.
}OctTree;


OctTree* newOctTree(Position pos, float mcord, Branch* par);

void addMeshToOcttree(OctTree* tree, float* positionMesh, float* colorMesh, uint meshSize);
void addPolygonToOcttree(OctTree* tree, float* posMesh);

void addOcttreeToOcttree(OctTree* added, OctTree* tree);   //add Tree somwhere at the end, should be used to place trees, furniture, etc
void addLeafToOcttree(Leaf* leaf, OctTree* tree);
void octTreeOutputConsole(OctTree* tree);

//graphics functions
const Vector3f* octTreeGetVertexArray(OctTree* tree);

//TODO delete
void octTreeAddNode(Voxel* voxPtr, OctTree* treePtr);
void octTreeDraw(OctTree* ptr);

#endif //DYNAMICOCTTREE_CI_OCTTREE_H
