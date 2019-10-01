//
// Created by axiom on 4/10/19.
//

#include "Window.h"
#include "../../shaders/Shader.h"

Window newWindow(){
    Window window;
    window.backColor[0] = 0.0f;
    window.backColor[1] = 0.2f;
    window.backColor[2] = 0.0f;
    window.backColor[3] = 1.0f;

    window.projection = matrics4fPerspective(1.5, (float)16/10, 0.1f, 4096.0f);

    window.view = Matrics4f_cam(Vector3fVal(512.0f, 512.0f, 512.0f),
                                Vector3fVal(514.0f, 515.0f, 516.0f),
                                Vector3fVal(212.0f, 312.0f, 412.0f));//todo original view parametres

    window.program = makeShaderProgram("../src/graphics/shaders/fragment001.fs",
                                       "../src/graphics/shaders/vertex001.vs");
    return window;
}
