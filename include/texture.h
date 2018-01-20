#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <png.h>

enum texture_error
{
    ERR_SUCCESS = 0,
    ERR_BAD_INPUT = -1,
    ERR_FAILED_OPENING_FILE = -2,
    ERR_FAILED_READING_FILE = -3,
    ERR_BAD_FILE_FORMAT = -4
};

typedef texture_error t_err_t;

class TextureLoader
{
    private:
        FILE *fp;
        png_bytep *row_pointers;
    public:
        TextureLoader();
        TextureLoader(const char *);

        void setFile(const char *);
        int readFile();
        unsigned char **getBuffer();
        
        t_err_t t_err;
};

#endif