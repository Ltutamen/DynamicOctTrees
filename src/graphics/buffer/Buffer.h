//
// Created by axiom on 4/27/19.
//

#ifndef DYNAMICOCTTREE_CI_BUFFER_H
#define DYNAMICOCTTREE_CI_BUFFER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <malloc.h>
#include "../../game/engine/mathematics/vectors/Vectors.h"

enum MemoryType {MT_Static = GL_STATIC_DRAW, MT_Dynamic = GL_DYNAMIC_DRAW, MT_Stream = GL_STREAM_DRAW};
enum BufferType {BT_VBO = GL_ARRAY_BUFFER, BT_SSBO = GL_SHADER_STORAGE_BUFFER, BT_AtomicCounter = GL_ATOMIC_COUNTER_BUFFER};

typedef struct{
    GLuint id;
    enum MemoryType mt;
    enum BufferType bt;

}Buffer;


Buffer* newBuffer(enum MemoryType _mt, enum BufferType _bt);


void deleteBuffer(Buffer* buff);


void bufferSetData(Buffer* buffer, void* data, uint size);
void bufferUpdateData(Buffer* buffer, void* data, uint size, uint offset);
//inline void bufferBindBase(Buffer* buffer, uint baseId);
//inline void bind(Buffer* base);
//inline void unbind(Buffer* base);

#endif //DYNAMICOCTTREE_CI_BUFFER_H
