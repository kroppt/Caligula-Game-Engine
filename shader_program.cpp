#include "shader_program.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include "utils.h"
#include <sstream>
#include <vector>

ShaderProgram::ShaderProgram(std::vector<GLuint> shaderList){
    // initialize OpenGL program and shader IDs
    programID_ = glCreateProgram();

    for(std::vector<GLuint>::iterator it = shaderList.begin(); it != shaderList.end(); it++){
        glAttachShader(programID_, *it);
    }

    glLinkProgram(programID_);

    // check for program errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programID_, GL_LINK_STATUS, &programSuccess);
    if(programSuccess != GL_TRUE){
        printProgramLog(programID_);
        throw std::invalid_argument("Error linking program");
    }

}

GLuint createShader(GLenum shaderType, const char *filename){
    GLuint shader = glCreateShader(shaderType);
    char *source = read(filename);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    free(source);

    // check for successful shader compilation
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(compiled != GL_TRUE) {
        printShaderLog(shader);
        throw std::invalid_argument("Unable to compile a shader");
    }
}

void ShaderProgram::bind(){
    glUseProgram(programID_);
}

void ShaderProgram::unbind(){
    glUseProgram(0);
}

void ShaderProgram::relink(){
    glLinkProgram(programID_);
}

// taken from http://lazyfoo.net/tutorials/SDL/51_SDL_and_modern_opengl/index.php
static void printProgramLog(GLuint program){
    if(glIsProgram(program)){
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        
        //Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        
        //Allocate string
        char* infoLog = (char*) malloc(sizeof(char) * maxLength);
        
        //Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if(infoLogLength > 0){
            printf("%s\n", infoLog);
        }
        
        //Deallocate string
        free(infoLog);
    }else{
        printf("Name %d is not a program\n", program);
    }
}

// taken from http://lazyfoo.net/tutorials/SDL/51_SDL_and_modern_opengl/index.php
static void printShaderLog(GLuint shader){
    if(glIsShader(shader)){
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        
        //Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        //Allocate string
        char* infoLog = (char*) malloc(sizeof(char) * maxLength);
        
        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if(infoLogLength > 0){
            printf("%s\n", infoLog);
        }

        //Deallocate string
        free(infoLog);
    }else{
        printf("Name %d is not a shader\n", shader);
    }
}
