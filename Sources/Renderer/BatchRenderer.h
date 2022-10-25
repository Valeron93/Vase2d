#pragma once

#include <Core/Common.h>
#include <Renderer/Shader.h>
#include <Renderer/Buffers.h>

struct BatchVertex {
    Vec2 position;
    Vec4 color;
};

class BatchRenderer {
private:

    static constexpr size_t MaxQuadsBatch = 10000;
    static constexpr size_t MaxVertices = MaxQuadsBatch * 4;

    static const std::string vertexShader;
    static const std::string fragmentShader;

    Unique<Shader> mShader;
    Unique<VertexArray> mVertexArray;
    Unique<IndexBuffer> mIndexBuffer;
    Unique<VertexBuffer> mVertexBuffer;

    BatchVertex* mBatchVertices;
    size_t mBatchVerticesIndex = 0;

public:
    BatchRenderer();
    ~BatchRenderer();

    BatchRenderer(BatchRenderer& batchRenderer) = delete;
    BatchRenderer(BatchRenderer&& batchRenderer) = delete;

public:
    void render(const Vec2& position, const Vec4& color);
    void flush();
    void setProjectionMatrix(const Mat4& projection);


};
