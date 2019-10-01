//
// Created by axiom on 5/10/19.
//

#include "../vectors/Vectors.h"

#ifndef DYNAMICOCTTREE_CI_MATRICS_H
#define DYNAMICOCTTREE_CI_MATRICS_H

typedef struct{
    float v[16];
}Matrics4f;


Matrics4f Matrics4f_null();
Matrics4f Matrics4f_one();
Matrics4f Matrics4f_cam(Vector3f cameraPosition, Vector3f cameraView, Vector3f headsUp);

void matrics4fMult(Matrics4f* result, Matrics4f arg);
Matrics4f matrics4fPersp(float fovRadians, float scrPerspective, float minDist, float maxDist);
void matrics4fPrint(Matrics4f matr);
Matrics4f Matrics4f_rand();
Matrics4f Matrics4fVal(float val);

Matrics4f matrics4fPerspective(float fovAngle, float ratio, float near, float far);
Matrics4f Matrics4f_cam(Vector3f cameraPosition, Vector3f cameraView, Vector3f headsUp);


#endif //DYNAMICOCTTREE_CI_MATRICS_H
