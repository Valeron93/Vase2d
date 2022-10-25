#pragma once

#include "glad/glad.h"

class VertexBuffer {
private:
    GLuint id {0};
    GLenum mDraw;

public:
    explicit VertexBuffer(GLenum draw = GL_STATIC_DRAW) {
        glGenBuffers(1, &id);
        mDraw = draw;
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &id);
    };

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void bufferData(void* vertices, size_t size) const {
        glBufferData(GL_ARRAY_BUFFER, (GLsizei) size, vertices, mDraw);
    }

    template <typename T>
    void uploadData(T *vertices, size_t count) const {
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(T), (void*)vertices);
    }

    void unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};