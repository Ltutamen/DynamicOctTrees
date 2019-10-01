//
// Created by axiom on 5/10/19.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>
#include "Matrics.h"

Matrics4f Matrics4f_null(){
    return Matrics4fVal(0.0f);
}


Matrics4f Matrics4fVal(float val){
    Matrics4f result;
    for(uint i=0 ; i<16 ; i++){
        result.v[i] = val;
    }
    return result;
}


Matrics4f Matrics4f_rand(){
    Matrics4f result;
    srand(112);
    for(uint i=0 ; i<16 ; i++){
        result.v[i]   = ((float)rand()/RAND_MAX) * 1.0f;

    }
    return result;
}


void matrics4fPrint(Matrics4f matr){
    putchar('\n');
    for(uint i=0 ; i<4 ; i++){
        for(uint j=0 ; j<4 ; j++){
            printf("\t%3.2f_", matr.v[4*i + j]);
        }
        printf("\n");
    }
}


Matrics4f Matrics4f_cam(Vector3f cameraPosition, Vector3f cameraView, Vector3f headsUp){
    printf("\ndeb: %f %f %f %f %f %f ", cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraView.x, cameraView.y, cameraView.z);
    Vector3f xaxis, yaxis, zaxis;
    zaxis = cameraView;
    zaxis = vec3fSub(&zaxis, cameraPosition);
    vec3fNormalize(&zaxis);
    vec3fPrint("mart4fcam NORM", zaxis);

    vec3fPrint("headsup test", headsUp);
    //vec3fPrint("buffer test", buffer);
    vec3fPrint("xaxis test", xaxis);
    vec3fPrint("yaxis test", yaxis);

    vec3fNormalize(&headsUp);
    vec3fCross(&headsUp, &zaxis);
    vec3fNormalize(&headsUp);
        xaxis.x = headsUp.x;
        xaxis.y = headsUp.y;
        xaxis.z = headsUp.z;

    Vector3f buffer;
    buffer.x = zaxis.x;
    buffer.y = zaxis.y;
    buffer.z = zaxis.z;

    //  here yyaxis is ok

    vec3fCross(&buffer, &xaxis);
        yaxis.x = buffer.x;
        yaxis.y = buffer.y;
        yaxis.z = buffer.z;
    //  XAXIS is WRONG!

    Matrics4f translation = Matrics4f_null();
    translation.v[3*4+0] = -cameraPosition.x;
    translation.v[3*4+1] = -cameraPosition.y;
    translation.v[3*4+2] = -cameraPosition.z;


    Matrics4f rotation = Matrics4f_null();
    //  xaxis are WRONG!
    rotation.v[0] = xaxis.x;
    rotation.v[4] = xaxis.y;
    rotation.v[8] = xaxis.z;
    rotation.v[1] = yaxis.x;
    rotation.v[5] = yaxis.y;
    rotation.v[9] = yaxis.z;
    rotation.v[2] = zaxis.x;
    rotation.v[6] = zaxis.y;
    rotation.v[10] = zaxis.z;

    printf("\n translation:");
    for(int i=0 ; i<16 ; i++)
        printf("%f ", translation.v[i]);
    printf("\n rotation:");
    for(int i=0 ; i<16 ; i++)
        printf("%f ", rotation.v[i]);


    matrics4fMult(&rotation, translation);

    return rotation;



 //   X = Y.Cross(Z);

}


Matrics4f matrics4fPerspective(float fovAngle, float ratio, float near, float far){
    Matrics4f result = Matrics4f_null();

    float tanHalf = tanh(fovAngle/2);
    result.v[0*4+0] = 1/(ratio*tanHalf);
    result.v[1*4+1] = 1/tanHalf;
    result.v[2*4+2] = -(far+near)/(far-near);
    result.v[3*4+2] = -1;
    result.v[2*4+3] = -(2*far*near)/(far-near);

    return result;



}


void matrics4fMult(Matrics4f* result, Matrics4f arg){
    Matrics4f buffer;
    for(uint i=0 ; i<16 ; i++)
        buffer.v[i] = result->v[i];

    float r;

    for(uint i=0 ; i<4 ; i++){
        for(uint k=0 ; k<4 ; k++){
            r = buffer.v[i*4+k];
            for(uint j=0 ; j<4 ; j++)
                result->v[i*4+j] += r*arg.v[k*4+j];
        }
    }
}