//
// Created by axiom on 4/10/19.
//

#ifndef DYNAMICOCTTREE_CI_WINDOW_H
#define DYNAMICOCTTREE_CI_WINDOW_H

#include <GL/gl.h>
#include "../../../game/engine/mathematics/vectors/Vectors.h"
#include "../../../game/engine/mathematics/matrices/Matrics.h"

typedef struct {
    Vector2ui size;

    Vector2ui pos;

    GLfloat backColor[4];

    Matrics4f projection;

    Matrics4f view;

    GLuint program;


}Window;

Window newWindow();


#endif //DYNAMICOCTTREE_CI_WINDOW_H
