#include "nus/io.h"
#if defined (UNIX)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>  
#elif defined (WINDOWS)
#include <windows.h>
#else
  // What OS is not POSIX or Windows? I have no idea -- so just error out
  #error "Your Operating System is neither POSIX (including Linux, Mac OS, and the BSDs) nor Windows and is not supported --\
did you configure your compiler correctly?"
#endif 

//get the size of a file
size_t name_file_size(const char *filename){
  FILE *f = fopen(filename, "rb");
  size_t ret = open_file_size(f);
  fclose(f);
  return ret;
}

size_t open_file_size(FILE *file){
  if(!file) return 0;
  #if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
  struct stat buffer;
  if( (fstat(fileno(file), &buffer) != 0) || (!S_ISREG(buffer.st_mode)) ){
    fclose(file);  return 0;
  }
  return (size_t)buffer.st_size;
  #elif defined (_WIN32) || defined (_WIN64)
    #ifndef q4_WCE
    long long len = 3;
    FlushFileBuffers((HANDLE) _get_osfhandle(_fileno(file)));
    HANDLE h = CreateFileMapping((HANDLE) _get_osfhandle(_fileno(file)), 0, PAGE_READONLY, 0, len, 0);
    #else
    FlushFileBuffers((HANDLE) _fileno(_file));
    HANDLE h = CreateFileMapping((HANDLE) _fileno(_file), 0, PAGE_READONLY, 0, len, 0);
    #endif //q4_WCE
  LARGE_INTEGER file_size;
  if (!GetFileSizeEx(file, &file_size)) {
    /* Handle error */
    file_size.QuadPart = 0;
  }
  CloseHandle(h);
  return (size_t) file_size.QuadPart;
  #else
  // What OS is not POSIX or Windows? I have no idea -- so just error out
  #error "Your Operating System is neither POSIX (including Linux, Mac OS, and the BSDs) nor Windows and is not supported --\
did you configure your compiler correctly?"
  #endif 
}

// loads a file into memory -- returns NULL on error
char *load_file(const char *filename){
  FILE *file = fopen(filename, "rb");
  if(!file) {
    perror("[nus io.c] Load file failed");
    return NULL;
  }
  size_t size = open_file_size(file);
  if(size == 0) return NULL;
  char *buffer = calloc(size, 1);
  size_t read = fread(buffer, 1, size, file);
  while(read != size && !feof(file)){
    read += fread(&buffer[read], 1, size-read, file);
  }
  fclose(file);
  return buffer;
}
