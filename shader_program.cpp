#include "shader_program.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include "utils.h"

using namespace std;

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

ShaderProgram::ShaderProgram(const char *vertexShaderFilename, const char *fragmentShaderFilename){
	// initialize OpenGL program and shader IDs
    programID_ = glCreateProgram();
	vertexShader_ = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);

	// extract shader source code
	const char *vertexShaderSource = read(vertexShaderFilename);
	const char *fragmentShaderSource = read(fragmentShaderFilename);

	// set and compile shader source code
	glShaderSource(vertexShader_, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader_);
	glShaderSource(fragmentShader_, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader_);

	// check for successful shader compilation
	GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &vShaderCompiled);
    if(vShaderCompiled != GL_TRUE) {
        printShaderLog(vertexShader_);
		throw invalid_argument("Unable to compile vertex shader");
    }

	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &fShaderCompiled);
	if(fShaderCompiled != GL_TRUE){
		printShaderLog(fragmentShader_);
		throw invalid_argument("Unable to compile fragment shader");
	}

	// attach shaders to program
	glAttachShader(programID_, vertexShader_);
	glAttachShader(programID_, fragmentShader_);
	glLinkProgram(programID_);

	// check for program errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(programID_, GL_LINK_STATUS, &programSuccess);
	if(programSuccess != GL_TRUE){
		printProgramLog(programID_);
		throw invalid_argument("Error linking program");
	}

}
