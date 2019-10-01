//
// Created by axiom on 4/10/19.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "../graphics/buffer/Buffer.h"
#include "engine/mathematics/vectors/Vectors.h"
#include <time.h>
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <math.h>

void runRender(Game* game);
void runInput(Game* game);
void initRender(Game* game);

Buffer* buffer;


const uint targetFPS = 2;
const uint targetUPS = 1;
const long clocksInSecond;


long clocksPerFrame;
long clocksPerUpdate;

Game newGame(){}

float  test[16] = {0.12f, 0.012f, 0.64f, 0.74f,
                   0.13f, 0.314f, 0.0334f, 0.53,
                   0.635f, 0.23f, 0.87f, 0.11f,
                   0.52f, 0.011f, 0.45f, 0.9f};


Game newGameOpenGlInit(OctTree* w){
    if (!glfwInit())
        exit(2);

    Game result;
    result.isRunning = GL_TRUE;
    result.world = w;
    result.gameProps = newGamePreoprties();
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


    result.window = glfwCreateWindow(1280, 800, "Spalax", NULL, NULL);
    result.winProperties.size.x = 1280;
    result.winProperties.size.y = 800;
    if(!result.window) {
        printf("Error making window");
        exit(2); //TODO error
    }

    glfwShowWindow(result.window);

    glfwMakeContextCurrent(result.window);
    printf("OpenGL version: %s \n", (char*)glGetString(GL_VERSION));

    if(glewInit() != GLEW_OK) {
        ///printf("%s", glewGetErrorString());
        exit(5);
    }

    glfwSetInputMode(result.window, GLFW_STICKY_KEYS, GL_TRUE);

    //VAO initialization
    glGenVertexArrays(1, &(result.VertexArrayID));
    glBindVertexArray(result.VertexArrayID);

    //Buffer Creation
    glGenBuffers(1, &result.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, result.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * w->elementsCount, octTreeGetVertexArray(w), GL_STATIC_DRAW);

    result.winProperties = newWindow();
    result.player = *newPlayer();
    result.matrixID = glGetUniformLocation(result.winProperties.program, "MWP");

    glfwSetInputMode(result.window, GLFW_STICKY_KEYS, GL_TRUE);

    return result;

}


void gameLoop(Game game){
    initRender(&game);

    clocksPerFrame = CLOCKS_PER_SEC/targetFPS;
    clocksPerUpdate = CLOCKS_PER_SEC/targetUPS;
    long clocksPerUpdateCycle = 0;

    printf("\n Clocks per sec %d", (int)CLOCKS_PER_SEC);

    long previous = clock() - clocksPerFrame;
    int i = 0;
    long lag = 0;

    while(game.isRunning == GL_TRUE){

        printf("\nLoop%i ", i);

        long current = clock();
        long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        for(uint j = 0 ; lag>=clocksPerUpdateCycle && j<targetUPS ; j++) {
            //runLogick();
            putchar('u');
            lag -= clocksPerUpdateCycle;
            clocksPerUpdateCycle = clock()- current;
        }

        while(lag >= clocksPerUpdateCycle){
            //runLogick();
            putchar('l');
            lag -= clocksPerUpdateCycle;
            clocksPerUpdateCycle = clock()- current;
        }
        runInput(&game);
        glfwPollEvents();

        runRender(&game);
        usleep((current+clocksPerFrame-clock()));
        i++;

        if(glfwGetKey(game.window, GLFW_KEY_ESCAPE ) == GLFW_PRESS &&
            glfwWindowShouldClose(game.window) != 0 );

    }

}


void initRender(Game* game){
    Matrics4f model = Matrics4fVal(1.0f);
    matrics4fMult(&game->winProperties.view, model);
    matrics4fMult(&game->winProperties.projection, game->winProperties.view);
    game->matrixID = glGetUniformLocation(game->winProperties.program, "MVP");


    //glPolygonMode(GL_FRONT, GL_FILL);
    //buffer = newBuffer(GL_STATIC_DRAW, GL_ARRAY_BUFFER);
    //bufferSetData(buffer, (void*)octTreeGetVertexArray(game->world), (uint)game->world->elementsCount*3);

}


void runRender(Game* game){
    putchar('r');

   __glewClearBufferfv(GL_COLOR, 0, game->winProperties.backColor);

    game->winProperties.backColor[0] = 0.2;
    game->winProperties.backColor[1] = 0.1;
    game->winProperties.backColor[2] = (float)sin(((double)clock()) / 100000);//sin((double)time(NULL));

    glUseProgram(game->winProperties.program);

    glUniformMatrix4fv(game->matrixID, 1, GL_FALSE, &game->winProperties.view);
    for(uint i=0 ; i<16  ; ++i)
        test[i] = rand()%1024 / 1000.0f ;

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, game->vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)game->world->elementsCount * 4);
    glDisableVertexAttribArray(0);
    glfwSwapBuffers(game->window);

}


void runInput(Game* game){
    //consts
    // todo: turn everything into radians
    float mouseSpeed = 0.005f;
    //  static double lastTime = glfwGetTime();


    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - game->gameProps.lastCycleTime);

    double xpos, ypos;
    glfwGetCursorPos(game->window, &xpos, &ypos);
    glfwSetCursorPos(game->window, (float)game->winProperties.size.x/2, (float)game->winProperties.size.y/2);

    game->player.horizontalAngle += mouseSpeed * (float)(game->winProperties.size.x/2 - xpos);
    game->player.vertivalAngle += mouseSpeed * (float)(game->winProperties.size.y/2 - ypos);

    Vector3f direction = Vector3fVal(
            cosf(game->player.vertivalAngle) * sinf(game->player.horizontalAngle),
            sinf(game->player.vertivalAngle),
            cosf(game->player.vertivalAngle) * cosf(game->player.horizontalAngle)
            );

    Vector3f right = Vector3fVal(
            sinf(game->player.horizontalAngle - (float)M_PI_2),
            0.0f,
            cosf(game->player.horizontalAngle - (float)M_PI_2)
            );

    Vector3f up = Vec3fCrossR(&right, &direction);

    game->player.pos = vec3fAdd(&game->player.pos, vec3fMulV(&direction , deltaTime * game->player.speed));
    /*
    if(glfwGetKey(game->window, GLFW_KEY_W) == GLFW_PRESS )
        game->player.pos = vec3fAdd(&game->player.pos, vec3fMulV(&direction , deltaTime * game->player.speed));
    */
    if(glfwGetKey(game->window, GLFW_KEY_S) == GLFW_PRESS )
        game->player.pos = vec3fSub(&game->player.pos, vec3fMulV(&direction , deltaTime * game->player.speed));

    if(glfwGetKey(game->window, GLFW_KEY_A) == GLFW_PRESS)
        game->player.pos = vec3fAdd(&game->player.pos, vec3fMulV(&right, deltaTime * game->player.speed));

    if(glfwGetKey(game->window, GLFW_KEY_A) == GLFW_PRESS)
        game->player.pos = vec3fSub(&game->player.pos, vec3fMulV(&right, deltaTime * game->player.speed));

    if(glfwGetKey(game->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        game->isRunning = GL_FALSE;

    float FoV = game->player.initialFOV;

    game->winProperties.projection = matrics4fPerspective(FoV, 1280 / 800, 0.1f, 1024.0f);

    game->winProperties.view = Matrics4f_cam(game->player.pos, vec3fAdd(&game->player.pos, game->player.view), up);
    for(int i=0 ; i<16 ; ++i)
        printf("%lf_", game->winProperties.view.v[i]);
    printf("\n");

    game->gameProps.lastCycleTime = currentTime;


}