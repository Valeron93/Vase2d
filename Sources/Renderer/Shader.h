#pragma once

#include <string>
#include <Platform/RenderAPI.h>
#include <Core/Logging.h>
#include <Core/Mathematics.h>

class Shader {

private:
    GLuint mShaderProgram {0};

private:

    static GLuint CompileShader(GLenum type, const char *source) {


        GLuint shader = RenderAPI::CreateShader(type);

        RenderAPI::ShaderSource(shader, 1, &source, nullptr);

        RenderAPI::CompileShader(shader);

        GLint success = GL_FALSE;
        RenderAPI::GetShaderIv(shader, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            GLint shaderLogLength = 511;
            char shaderCompileLog[512];

            RenderAPI::GetShaderInfoLog(shader, shaderLogLength, &shaderLogLength, shaderCompileLog);

            VASE_LOG_ERROR("Failed to compile shader! " << shaderCompileLog);
            exit(1);

        }

        return shader;
    }

public:

    Shader() = delete;

    Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {

        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc.c_str());

        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc.c_str());

        mShaderProgram = RenderAPI::CreateProgram();

        RenderAPI::AttachShader(mShaderProgram, vertexShader);
        RenderAPI::AttachShader(mShaderProgram, fragmentShader);

        RenderAPI::LinkProgram(mShaderProgram);

        RenderAPI::DeleteShader(vertexShader);
        RenderAPI::DeleteShader(fragmentShader);
    }

    ~Shader() {
        RenderAPI::DeleteProgram(mShaderProgram);
    }

private:
    inline GLint getLocation(const char* name) const {
        return RenderAPI::GetUniformLocation(mShaderProgram, name);
    }

public:
    inline GLuint getShaderProgram() const {
        return mShaderProgram;
    }

    inline void bind() const {
        RenderAPI::UseProgram(mShaderProgram);
    }

    inline void unbind() const {
        RenderAPI::UseProgram(0);
    }


    inline void setUniformFloat(const char* name, float value) const {
        RenderAPI::Uniform1Float(getLocation(name), value);
    }

    inline void setUniformMat4(const char* name, const Mat4& matrix) const {
        RenderAPI::UniformMat4(getLocation(name), false, matrix);
    }

    inline void setUniformVec3(const char* name, const Vec3& vector) const {
        RenderAPI::UniformVec3(getLocation(name), vector);
    }

    inline void setUniformInt(const char* name, int value) const {
        RenderAPI::UniformInt(getLocation(name), value);
    }

    inline void setUniformVec2(const char* name, const Vec2& vector) const {
        RenderAPI::UniformVec2(getLocation(name), vector);
    }


    inline void setUniformVec4(const char* name, const Vec4& vector) const {
        RenderAPI::UniformVec4(getLocation(name), vector);
    }

    inline void setProjectionMatrix(const Mat4& projection) const {
        setUniformMat4("mProjection", projection);
    }

    inline void setViewMatrix(const Mat4& view) const {
        setUniformMat4("mView", view);
    }

    inline void setModelMatrix(const Mat4& model) const {
        setUniformMat4("mModel", model);
    }

    inline void setUniformFloatArray(const char *name, float *array, GLsizei count) const {
        RenderAPI::UniformFloatArray(getLocation(name), array, count);
    }

    inline void setUniformVec2Array(const char* name, float *values, GLsizei count) const {
        RenderAPI::UniformVec2Array(getLocation(name), values, count);
    }
};

