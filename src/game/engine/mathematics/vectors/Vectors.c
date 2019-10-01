//
// Created by axiom on 3/29/19.
//

#include <math.h>
#include <malloc.h>
#include "Vectors.h"

Vector3f* newVector3f(const float a, const float b, const float c){
    Vector3f* result = (Vector3f*)malloc(sizeof(Vector3f));
    result->x = a;
    result->y = b;
    result->z = c;
    return result;
}


void vec3fNormalize(Vector3f* arg){
    float norm = sqrtf(arg->x*arg->x + arg->y*arg->y + arg->z*arg->z);
    float deb = (arg->x*arg->x) + (arg->y*arg->y) + (arg->z*arg->z);
    deb = sqrtf(deb);
    arg->x /= norm;
    arg->y /= norm;
    arg->z /= norm;
}


Vector3f vec3fSub(Vector3f* a, Vector3f b){
    Vector3f result;
    result.x = a->x - b.x;
    result.y = a->y - b.y;
    result.z = a->z - b.z;
    return result;
}


Vector3f vec3fAdd(Vector3f* a, Vector3f b){
    Vector3f result;
    result.x = a->x + b.x;
    result.y = a->y + b.y;
    result.z = a->z + b.z;
    return result;
}



void vec3fCross(Vector3f* result, Vector3f* sub){
    Vector3f buff;
    buff.x = result->x;
    buff.y = result->y;
    buff.z = result->z;

    result->x = buff.y*sub->z - buff.z*sub->y;
    result->y = buff.z*sub->x - buff.x*sub->z;
    result->z = buff.x*sub->y - buff.y*sub->x;
}


Vector3f Vec3fCrossR(Vector3f* a, Vector3f* b){
    Vector3f result;

    result.x = a->x*b->z - a->z*b->y;
    result.y = a->z*b->x - a->x*b->z;
    result.z = a->x*b->y - a->y*b->x;

    return result;

}


Vector3f Vector3fVal(const float a, const float b, const float c){
    Vector3f result;
    result.x = a;
    result.y = b;
    result.z = c;

    return result;
}


Vector3f vec3fMul(Vector3f* a, Vector3f* b){
    Vector3f result;
    result.x = a->x * b->x;
    result.y = a->y * b->y;
    result.z = a->z * b->z;

    return result;
}


Vector3f vec3fMulV(Vector3f* a, float b){
    Vector3f result;
    result.x = a->x * b;
    result.y = a->y * b;
    result.z = a->z * b;
    return result;
}


void vec3fPrint(const char* string, Vector3f vector){
    printf("\n\t%s\n", string);
    printf(" %f %f %f\n", vector.x, vector.y, vector.z);
}