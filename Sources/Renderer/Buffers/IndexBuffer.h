#pragma once

#include <Platform/RenderAPI.h>
class IndexBuffer {
private:
    GLuint id {0};

public:
    explicit IndexBuffer() {
        RenderAPI::GenerateBuffers(1, &id);
    }

    void bufferData(void* indices, size_t size, GLenum draw=GL_STATIC_DRAW) {
        RenderAPI::ElementArrayBufferData(size, indices, draw);
    }

    ~IndexBuffer() {
        RenderAPI::DeleteBuffers(1, &id);
    };

    void bind() const {
        RenderAPI::BindElementArrayBuffer(id);
    }

    void unbind() const {
        RenderAPI::BindElementArrayBuffer(id);
    }
};