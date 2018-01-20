/**
  NusgartLib common header -- provides common macros
  Copyright 2016 Nicholas Nusgart.
 */
#ifndef _NUS_COMMON_H
#define _NUS_COMMON_H 1
//includes
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
///////////////////////SYSTEM TYPE DEFINITIONS
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#define UNIX
#elif defined (_WIN32) || defined (_WIN64)
#define WINDOWS
#else
#error "UNKNOWN OS -- submit patches if you want it to work"
#endif
////////////////////////
//define error utilities
#define eputs(x) fputs(x, stderr)
#define eprintf(x, ...) fprintf(stderr, x, __VA_ARGS__)
/// contracts
#define CONTRACT(_x) do{ if(!(_x)){ eprintf("Assertion %s in file %s line %d failed -- Caller broke contract.\n", #_x , __FILE__,  __LINE__); abort(); } }while(0)
#define ASSERT(_x)  do{ if(!(_x)){ eprintf("Assertion %s in file %s line %d failed -- Unexpected assertion failure.\n", #_x , __FILE__,  __LINE__); abort(); } }while(0)
//////////////end
#endif
