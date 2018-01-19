#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <glad/glad.h>

class ShaderProgram{
    public:
        ShaderProgram (const char *vertexShaderFilename, const char *fragmentShaderFilename);
        GLuint getVertexShader () { return vertexShader_; }
        GLuint getFragmentShader () { return fragmentShader_; }
        GLuint getProgramID () { return programID_; }
        void bind();
        void unbind();
        void relink();
    private:
        GLuint vertexShader_, fragmentShader_;
        GLuint programID_;
};

#endif
