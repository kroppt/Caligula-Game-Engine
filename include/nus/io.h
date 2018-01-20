/**
  NusgartLib IO header -- provides IO utility functions
  Copyright 2016 Nicholas Nusgart.
 */
#ifndef _NUS_IO_H
#define _NUS_IO_H 1
// includes
#include "nus/common.h"
//definitions
#ifdef _cplusplus
extern "C"{
#endif
//get the size of a file
size_t name_file_size(const char *filename);
size_t open_file_size(FILE *file);
// loads a file into memory -- returns NULL on error
char *load_file(const char *filename);
// 

#ifdef _cplusplus
}
#endif
#endif
