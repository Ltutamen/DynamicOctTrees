#include <stdio.h>
#include <math.h>
#include <malloc.h>

#include <GL/glew.h>
#include "GL/gl.h"
#include "src/octTrees/dynamicOctTree/octtree/OctTree.h"
#include "src/game/Game.h"
#include "test/MathTest.h"


#ifdef SAFE
 #undef SAFE
#endif
#define PRECISE

int machineCheck();
void openGLInit();
void openGLDismiss();
OctTree* getEmptyTree();
OctTree* testTree();
void testMath();
void getArrayTest();
void treeTestLoop();

#include <time.h>

int main() {
    //  testMath();
    Game game = newGameOpenGlInit(testTree());
    //getArrayTest();

    //  treeTestLoop();

    //  openGLInit();
    gameLoop(game);
    return 0;
}


int machineCheck(){
    if(sizeof(uint32)!=4)       return 1;
    if(sizeof(NTYPE_BRANCH)!=4) return 1;
    return 0;//no mistakes
}


void testMath(){
    printf("\n\n");
    printf("sqrtf test: %f %f", sqrtf(11.0f), sqrtf(0.00000099f));
    printf("gfsgdgdfgrgergrg");
    Matrics4f matr = Matrics4f_null();
    matr.v[0] = 3.0f;
    matr.v[5] = 4.0f;
    matr.v[10] = 3.0f;
    matr.v[15] = 9.0f;

    Matrics4f arg = Matrics4f_rand();

    matrics4fPrint(matr);
    matrics4fPrint(arg);
    matrics4fMult(&matr, arg);

    matrics4fPrint(matr);

    testMatrices();
}


OctTree* testTree(){
    printf("%s ", glGetString(GL_VERSION));
    OctTree* tree = newOctTree(Vector3fVal(0.f, 0.f, 0.f), 1024.f, nullptr);
    float posMesh[3*3] = { 0.0f, 0.0f, 0.0f,
                            -512.0f, 0.0f, 0.0f,
                            0.0f, -512.0f, 0.0f};

    float colMesh[3*3] = {0.33f, 0.11f, 0.62f,
                           0.97f, 0.52f, 0.16f,
                           0.68f, 0.87f, 0.44f};

    addMeshToOcttree(tree, posMesh, colMesh, 11);
    float polMesh[3*3] = {0.1f, 0.0f, 0.0f,
                        0.0, 512.0f, 0.0f,
                        20.0f, 0.0f, 0.0f};

    addPolygonToOcttree(tree, polMesh);
    const Vector3f* mesh = octTreeGetVertexArray(tree);

    return tree;

}


void treeTestLoop(){
    int isRunning = GL_TRUE;
    OctTree* tree = newOctTree((Position){0.f, 0.f, 0.f}, 1024.f, nullptr);

    while(isRunning){
        printf("Do what:\n 1.Show tree.\n 2.Add to tree\n 3.Remove from tree\n 4.exit");
        char input = (char)getchar();

        switch (input){
            case '1':{
                octTreeOutputConsole(tree);
                break;
            }
            case '2':{
                printf("\n Write n");
                uint n;
                scanf("%u", &n);
                float* tempMesh = (float*)malloc(sizeof(float) * 3 * n);

                for (int i = 0; i < n; ++i) {
                    printf("enter %i-th pol:\n ", i);
                    float a, b, c;
                    scanf("%f %f %f ", &a, &b, &c);
                    tempMesh[i*3] = a;
                    tempMesh[i*3 + 1] = b;
                    tempMesh[i*3 + 2] = c;
                }
                addMeshToOcttree(tree, tempMesh, tempMesh, n);

                break;
            }
            case '3':{

                break;
            }
            case '4':{
                isRunning = GL_FALSE;
                break;
            }
            default:{
                printf("\n wrong input\n");
            }
            scanf("%s", nullptr);
        }
    }
}