#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <glad/glad.h>
#include <vector>

GLuint createShader(GLenum shaderType, const char *filename);

class ShaderProgram{
    public:
		ShaderProgram (std::vector<GLuint> shaderList);
        ShaderProgram (const char* vertexShaderName, const char* fragmentShaderName);
        GLuint getProgramID () { return programID_; }
        void bind();
        void unbind();
        void relink();
    private:
        GLuint programID_;
};

#endif
