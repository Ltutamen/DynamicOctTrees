#ifndef _VECTORS_H_
#define _VECTORS_H_

#ifndef NULL
 #define NULL ((void *)0)
#endif
#ifndef nullptr
    #define nullptr ((void *)0)
#endif

#include <stdint.h>

//#define NEW_SPOSITION(xx,yy,zz,str) Position str;{str.x=(x),str.y=(y),str.z=(z);}

typedef int32_t int32;
typedef uint32_t uint32;
typedef long long unsigned ullong;

typedef struct {
    int x;
    int y;
    int z;
}Vector3i;

typedef unsigned int uint;

typedef struct {
    double x;
    double y;
    double z;
}Vector3d;

typedef struct{
    float x;
    float y;
    float z;
}Vector3f;

typedef struct {
    uint x;
    uint y;
}Vector2ui;

typedef Vector3f Position;

typedef Vector3f Color;


Vector3f* newVector3f(const float a, const float b, const float c);
Vector3f Vector3fVal(const float a, const float b, const float c);

void vec3fNormalize(Vector3f* arg);

//writes result into first argument
void vec3fCross(Vector3f* result, Vector3f* sub);

//returns new vector
Vector3f Vec3fCrossR(Vector3f* a, Vector3f* b);

Vector3f vec3fMul(Vector3f* a, Vector3f* b);

Vector3f vec3fAdd(Vector3f* a, Vector3f b);
Vector3f vec3fSub(Vector3f* a, Vector3f b);

Vector3f vec3fMulV(Vector3f* a, float b);

//  debug and output
void vec3fPrint(const char* string, Vector3f vector);
#endif