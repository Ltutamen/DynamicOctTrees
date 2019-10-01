//
// Created by axiom on 6/7/19.
//

#include <stdio.h>
#include "MathTest.h"
#include "../src/game/engine/mathematics/matrices/Matrics.h"
#include "../src/game/engine/mathematics/operations/Sqrt.h"

void testMatrices(){
    Matrics4f testmat = Matrics4f_cam(*newVector3f(1.0f, 10.0f, 100.0f), *newVector3f(0.3f, 0.3f, sqrtf(0.82f)), *newVector3f(0.0f, 1.0f, 0.0f));
    printf("\n matr out:");
    for(int i=0 ; i<16 ; i++) {
        printf("%f ", testmat.v[i]);
        if(!i%4)
            putchar('\n');
    }
    getchar();


}