#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <glad/glad.h>
#include <vector>

static void printProgramLog(GLuint program);
static void printShaderLog(GLuint shader);
GLuint createShader(GLenum shaderType, const char *filename);

class ShaderProgram{
    public:
		ShaderProgram (std::vector<GLuint> shaderList);
        GLuint getProgramID () { return programID_; }
        void bind();
        void unbind();
        void relink();
    private:
        GLuint programID_;
};

#endif
