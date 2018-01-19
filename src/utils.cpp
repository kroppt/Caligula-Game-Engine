#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <stdexcept>
#include <sstream>

char* read(const char *filename){
    FILE *fp = fopen(filename, "r");
    
    if(fp == NULL){
        std::ostringstream oss;
        oss << "Error in opening \"" << filename << "\"\n";
        throw std::invalid_argument(oss.str());
    }

    // seek to end of file to determine length
    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    // reset file position indicator to beginning of file
    fseek(fp, 0, SEEK_SET);

    // allocate space for contents and read into contents
    char *contents = (char*) malloc(sizeof(char) * len);
    fread(contents, sizeof(char), len, fp);
    fclose(fp);

    return contents;
}