#include "BatchRenderer.h"

const std::string BatchRenderer::vertexShader = R"(#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec4 oColor;

uniform mat4 mProjection = mat4(1.0f);

void main() {
    oColor = aColor;
    gl_Position = mProjection * vec4(aPos, 0.0f, 1.0f);
}

)";

const std::string BatchRenderer::fragmentShader = R"(#version 330 core

out vec4 FragColor;

in vec4 oColor;

void main() {
    FragColor = oColor;
}

)";

BatchRenderer::BatchRenderer() {

    mShader = MakeUnique<Shader>(vertexShader, fragmentShader);

    mVertexArray = MakeUnique<VertexArray>();
    mVertexArray->bind();

    mVertexBuffer = MakeUnique<VertexBuffer>(GL_DYNAMIC_DRAW);
    mVertexBuffer->bind();
    mVertexBuffer->bufferData(nullptr, MaxVertices * sizeof(BatchVertex));

    mIndexBuffer = MakeUnique<IndexBuffer>();
    mIndexBuffer->bind();

    auto indices = new uint32_t[MaxQuadsBatch * 6];

    for (size_t i = 0, offset = 0; i < MaxQuadsBatch * 6; i += 6, offset += 4) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;
        indices[i + 3] = 2 + offset;
        indices[i + 4] = 1 + offset;
        indices[i + 5] = 3 + offset;
    }

    mIndexBuffer->bufferData(indices, MaxVertices * sizeof(uint32_t), GL_DYNAMIC_DRAW);
    delete[] indices;

    mVertexArray->pushProperty<BatchVertex>(GL::Type::Float, 2);
    mVertexArray->pushProperty<BatchVertex>(GL::Type::Float, 4);

    mBatchVertices = new BatchVertex[MaxVertices];
}

BatchRenderer::~BatchRenderer() {
    delete[] mBatchVertices;
}

void BatchRenderer::render(const Vec2& position, const Vec4& color) {

    if (mBatchVerticesIndex >= MaxVertices) {
        flush();
    }

    size_t i = mBatchVerticesIndex;

    static const Vec2 vertices[] = {
            Vec2(-0.5f, -0.5f),
            Vec2(0.5f, -0.5f),
            Vec2(-0.5f,  0.5f),
            Vec2(0.5f, 0.5f),
    };

    mBatchVertices[i + 0] = {vertices[0] + position, color};
    mBatchVertices[i + 1] = {vertices[1] + position, color};
    mBatchVertices[i + 2] = {vertices[2] + position, color};
    mBatchVertices[i + 3] = {vertices[3] + position, color};

    mBatchVerticesIndex += 4;

}

void BatchRenderer::flush() {

    if (mBatchVerticesIndex == 0) {
        return;
    }

    mShader->bind();
    mVertexArray->bind();

    mVertexBuffer->bufferData(mBatchVertices, mBatchVerticesIndex * sizeof(BatchVertex));
    glDrawElements(GL_TRIANGLES, mBatchVerticesIndex / 4 * 6, GL_UNSIGNED_INT, nullptr);

    mBatchVerticesIndex = 0;

}

void BatchRenderer::setProjectionMatrix(const Mat4& projection) {

    mShader->bind();
    mShader->setProjectionMatrix(projection);
}
