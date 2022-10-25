#pragma once

#include "glad/glad.h"

class VertexArray {
private:
    GLuint mId {0};
    GLsizeiptr mTotalSize {0};
    GLsizei mIndex {0};

public:
    explicit VertexArray() {
        RenderAPI::GenerateVertexArrays(1, &mId);
    }

    void bind() const {
        glBindVertexArray(mId);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    template <typename T>
    void pushProperty(GL::Type type, size_t count) {

        GLsizei size;

        switch (type) {
            case GL::Type::Unsigned:
                size = sizeof(GLuint);
                break;

            case GL::Type::Float:
                size = sizeof(GLfloat);
                break;

            default:
                VASE_LOG_ERROR("Vertex attrib size is zero");
                exit(1);
                size = 0;
                break;
        }

        assert(size != 0);

        glEnableVertexAttribArray(mIndex);
        RenderAPI::VertexAttributePointer(mIndex, count, type, false, sizeof(T), (void*)mTotalSize);

        mIndex++;
        mTotalSize += count * size;
    }

};