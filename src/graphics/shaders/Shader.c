//
// Created by axiom on 4/14/19.
//

#include <stdio.h>
#include <GL/glew.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

GLchar* getShaderFile(char* filepath);
const GLint* strLen(const char* str);

GLuint makeShaderProgram(char* fragmentFPath, char* vertexFPath){

    GLchar* verShSource = getShaderFile(vertexFPath);
    //printf("%s ", verShSource);

    GLchar* fragShSource = getShaderFile(fragmentFPath);
    //printf("%s ", fragShSource);

    GLuint vertexShaderID = __glewCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &verShSource, NULL);
    glCompileShader(vertexShaderID);

    GLint result = GL_FALSE;
    GLint infoLogLen;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLen);
    if(infoLogLen > 0){
        char* shaderErrorMessage = (char*)malloc(infoLogLen * sizeof(char));
        glGetShaderInfoLog(vertexShaderID, infoLogLen, NULL, shaderErrorMessage);
        printf("\nVertexShader creation error: %s\n",shaderErrorMessage);
    }

    GLuint fragmentShader = __glewCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLen);
    if ( infoLogLen > 0 ){
        char* shaderErrorMessage = (char*)malloc(infoLogLen * sizeof(char));
        glGetShaderInfoLog(fragmentShader, infoLogLen, NULL, shaderErrorMessage);
        printf("\nFragmentShader creation error: %s\n", shaderErrorMessage);
    }


    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShaderID);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDetachShader(program, vertexShaderID);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShader);

    return program;

}


GLchar* getShaderFile(char* filepath){
    FILE* f = fopen(filepath, "rt");
    if(!f) {
        fopen(filepath, "a+");
        printf("ERROR opening shader file %s\n",filepath);
        exit(4);
    }

    long fileLen;
    fseek(f, 0, SEEK_END);
    fileLen = ftell(f);
    fseek(f, 0, SEEK_SET);

    GLchar* result = (char*)malloc(sizeof(GLchar) * (fileLen+1) );

    int c;
    int i;
    for(i=0 ; ( (c=getc(f))!=EOF ) ; i++ ){
        result[i] = (GLchar)c;
        //putchar(c);
    }
    result[i] = '\0';
    fclose(f);

    return result;
}


const GLint* strLen(const char* str){
    GLint* result = (GLint*)malloc(sizeof(GLint));
    for(*result = 0 ; str[*result]!='\0' ; (*result)++);

    return result;
}
