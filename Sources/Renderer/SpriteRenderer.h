#pragma once

#if 0

#include <Common.h>
#include <Mathematics.h>

#include <Renderer/Shader.h>

#include <Renderer/ScopedBind.h>
#include <Renderer/Buffers.h>
#include <Platform/RenderAPI.h>

#include <Logging.h>

/*
struct BatchVertex {
    GLuint index;
    Vec3 position;
    Vec4 color;
    Vec2 scale;
}; */

struct sBatchVertex {
    Vec2 position;
    Vec4 color;
};


class SpriteRenderer {

private:
    constexpr static int cBatchMaximum = 50000;

    const static std::string batchVertexShader;
    const static std::string batchFragmentShader;

    std::vector<sBatchVertex> vertices {};
    std::unique_ptr<Shader> mShader;
    std::unique_ptr<VertexArray> mVertexArray;
    std::unique_ptr<VertexBuffer> mVertexBuffer;
    std::unique_ptr<IndexBuffer> mIndexBuffer;

    sBatchVertex *mVertices;
    size_t mArrayIndex {0};
    //const size_t cMaxVertices;

public:

    SpriteRenderer()
    {
//        mShader = std::make_unique<Shader>(batchVertexShader, batchFragmentShader);
//        mVertexBuffer = std::make_unique<VertexBuffer>(GL_DYNAMIC_DRAW);
//        mVertexArray = std::make_unique<VertexArray>();
//
//        VASE_LOG_INFO("Vertex buffer is " << cMaxVertices * sizeof(BatchVertex));
//        //mIndexBuffer = std::make_unique<IndexBuffer>();
//
//        static float quadVertices[] = {
//                -0.5f, -0.5f,
//                -0.5f,  0.5f,
//                 0.5f, -0.5f,
//                 0.5f,  0.5f
//        };
//
//
//
//        mVertices = new BatchVertex[cMaxVertices];
//
//        auto indices = new uint32_t[cMaxVertices];
//
//        delete[] indices;
//
//        ScopedBind bindVertexArray(mVertexArray);
//        ScopedBind bindVertexBuffer(mVertexBuffer);
//        ScopedBind bShader(mShader);
//        //ScopedBind bIndexBuffer(mIndexBuffer);
//
//        mVertexBuffer->bufferData(nullptr, cMaxVertices * sizeof(BatchVertex));
//
//        mVertexArray->pushProperty<BatchVertex>(GL::Type::Unsigned, 1);
//        mVertexArray->pushProperty<BatchVertex>(GL::Type::Float, 3);
//        mVertexArray->pushProperty<BatchVertex>(GL::Type::Float, 4);
//        mVertexArray->pushProperty<BatchVertex>(GL::Type::Float, 2);
//
//        mShader->setUniformVec2Array("mVertices", quadVertices, 4);

        mShader = std::make_unique<Shader>(batchVertexShader, batchFragmentShader);

        mVertexArray = std::make_unique<VertexArray>();
        mVertexArray->bind();


        uint32_t indices[cBatchMaximum];
        for (uint32_t i = 0, offset = 0; i < cBatchMaximum; i += 6, offset += 4) {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
        }

        mVertexBuffer = std::make_unique<VertexBuffer>(GL_DYNAMIC_DRAW);
        mVertexBuffer->bind();
        mVertexBuffer->bufferData(nullptr, cBatchMaximum * sizeof(BatchVertex));


        // [x, y], [r, g, b, a]
        mVertexArray->pushProperty<BatchVertex>(GL::Type::Float, 2);
        mVertexArray->pushProperty<BatchVertex>(GL::Type::Float, 4);


        mIndexBuffer = std::make_unique<IndexBuffer>();
        mIndexBuffer->bind();


        mIndexBuffer->bufferData(indices, sizeof(indices));

        mVertexArray->unbind();
        mVertexBuffer->unbind();
        mIndexBuffer->unbind();

    }

    ~SpriteRenderer() {
        delete[] mVertices;
    }

    void render(const Vec2& position, const Vec4& color)
    {
        mVertices[mArrayIndex + 0] = {position, color};
        mVertices[mArrayIndex + 1] = {position, color};
        mVertices[mArrayIndex + 2] = {position, color};
        mVertices[mArrayIndex + 3] = {position, color};

        mArrayIndex += 4;
    }


    void flush()
    {
        mVertexBuffer->bind();
        mVertexBuffer->uploadData<BatchVertex>(mVertices, mArrayIndex);

        mShader->bind();
        mVertexArray->bind();

        if (mArrayIndex == 0) {
            return;
        }

        glDrawElements(GL_TRIANGLES, (mArrayIndex >> 2) * 6, GL_UNSIGNED_INT, nullptr);

        mArrayIndex = 0;
    }

    void setProjectionMatrix(const glm::mat4& projection)
    {
        ScopedBind bShader(mShader);
        mShader->setProjectionMatrix(projection);
    }


};

#endif

