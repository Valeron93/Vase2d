#pragma once

#include <Core/Mathematics.h>
#include <glad/glad.h>

namespace GL {

    enum class Type {
        Unsigned = GL_UNSIGNED_INT,
        Float = GL_FLOAT,
    };
}

class RenderAPI {
public:

    inline static void SetClearColor(const Vec4& color = Vec4(0.0f, 0.0f, 0.0f, 1.0f)) {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    inline static void Clear(const Vec4& color = Vec4(1.0f)) {
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline static void Viewport(int w, int h) {
        glViewport(0, 0, w, h);
    }

    inline static void GenerateBuffers(GLsizei count, GLuint *idPointer) {
        glGenBuffers(count, idPointer);
    }

    inline static void DeleteBuffers(GLsizei count, GLuint *idPointer) {
        glDeleteBuffers(count, idPointer);
    }

    inline static void ElementArrayBufferData(GLsizeiptr size, void* indices, GLenum drawType = GL_STATIC_DRAW) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, drawType);
    }

    inline static void BindElementArrayBuffer(GLuint id) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    inline static GLuint CreateShader(GLenum type) {
        return glCreateShader(type);
    }

    inline static void ShaderSource(GLuint shader, GLsizei count, const char** sources, GLsizei* length) {
        glShaderSource(shader, count, sources, length);
    }

    inline static void CompileShader(GLuint shader) {
        glCompileShader(shader);
    }

    inline static void GetShaderIv(GLuint shader, GLenum type, GLint *length) {
        glGetShaderiv(shader, type, length);
    }

    inline static void GetShaderInfoLog(GLuint shader, GLint length, GLint *lengthPointer, char *log) {
        glGetShaderInfoLog(shader, length, lengthPointer, log);
    }

    inline static void AttachShader(GLuint program, GLuint shader) {
        glAttachShader(program, shader);
    }

    inline static void LinkProgram(GLuint program) {
        glLinkProgram(program);
    }

    inline static void DeleteShader(GLuint shader) {
        glDeleteShader(shader);
    }

    inline static GLuint CreateProgram() {
        return glCreateProgram();
    }

    inline static void DeleteProgram(GLuint program) {
        glDeleteProgram(program);
    }

    inline static GLint GetUniformLocation(GLuint program, const char *name) {
        return glGetUniformLocation(program, name);
    }

    inline static void UseProgram(GLuint program) {
        glUseProgram(program);
    }

    inline static void Uniform1Float(GLint location, float value) {
        glUniform1f(location, value);
    }

    inline static void UniformMat4(GLint location, bool transpose, const Mat4& value) {
        glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value));
    }


    inline static void UniformVec3(GLint location, const Vec3& vec) {
        glUniform3fv(location, 1, glm::value_ptr(vec));
    }

    inline static void UniformVec2(GLint location, const Vec2& vec) {
        glUniform2fv(location, 1, glm::value_ptr(vec));
    }

    inline static void UniformInt(GLint location, int value) {
        glUniform1i(location, value);
    }

    inline static void UniformVec4(GLint location, const Vec4& vec) {
        glUniform4fv(location, 1, glm::value_ptr(vec));
    }

    inline static void UniformFloatArray(GLint location, float* values, GLsizei count) {
        glUniform1fv(location, count, values);
    }

    inline static void UniformVec2Array(GLint location, float *values, GLsizei count) {
        glUniform2fv(location, count, values);
    }

    inline static void DrawArrays(GLenum type, GLint first, GLsizei count) {
        glDrawArrays(type, first, count);
    }

    inline static void DrawTriangleArrays(GLint first, size_t count) {
        DrawArrays(GL_TRIANGLES, first, count);
    }

    inline static void GenerateVertexArrays(GLsizei count, GLuint *idPointer) {
        glGenVertexArrays(count, idPointer);
    }

    static void VertexAttributePointer(uint32_t index, size_t count, GL::Type type, bool normalized, size_t stride, void *pointer) {
        glVertexAttribPointer(index, (GLint) count, (GLenum) type, normalized, (GLsizei) stride, pointer);
    }
};