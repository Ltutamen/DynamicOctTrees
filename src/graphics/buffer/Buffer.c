//
// Created by axiom on 4/27/19.
//

#include "Buffer.h"


Buffer* newBuffer(enum MemoryType _mt, enum BufferType _bt){
    Buffer* result = (Buffer*)malloc(sizeof(Buffer));

    result->bt = _bt;
    result->mt = _mt;
    __glewGenBuffers(1, &(result->id));

    return result;
}


void deleteBuffer(Buffer* buff){
    __glewDeleteBuffers(1, &(buff->id));
    free(buff);
}


void bufferSetData(Buffer* buff, void* data, uint size){
    __glewBindBuffer(buff->bt, buff->id);
    __glewBufferData(buff->bt, size, data, buff->mt);
    __glewBindBuffer(buff->bt, 0);
}


void bufferUpdateData(Buffer* buffer, void* data, uint size, uint offset){
    glBindBuffer(buffer->bt, buffer->id);
    glBufferData(buffer->bt, offset, &size, GL_STATIC_DRAW);
    glBindBuffer(buffer->bt, 0);
}

inline void bufferBindBase(Buffer* buffer, uint baseId){
    glBindBufferBase(buffer->bt, baseId, buffer->id);
}

inline void bind(Buffer* buffer){
    glBindBuffer(buffer->bt, buffer->id);
}

inline void unbind(Buffer* base){
    glBindBuffer(base->bt, 0);
}