/**
  NusgartLib Linear Algebra header -- provides an implementation of vectors and matrices
  Copyright 2016 Nicholas Nusgart.
 */
#ifndef _NUS_LINALG_H
#define _NUS_LINALG_H 1
#include <tgmath.h>
#include "nus/common.h"
#ifdef _cplusplus
extern "C"{
#endif
//// Vector section
typedef union vec4{
  float v[4];
  struct {
    float x, y, z, w;
  };
} vec4;
//returns the sum of the two vectors
vec4 vec4_add(vec4 a , vec4 b);
//return a - b
vec4 vec4_sub(vec4 a, vec4 b);
//returns the dot product of the two vectors
float vec4_dot(vec4, vec4);
//
vec4 vec4_scalar_mult(vec4, float);
// is identical to vec3 cross and sets w to 1.0
vec4 vec4_cross(vec4, vec4);
//
vec4 vec4_reflect(vec4, vec4);
//returns the projection of a onto b
vec4 vec4_project(vec4 a, vec4 b);
//
float vec4_len(vec4);
//
vec4 vec4_norm(vec4);
////Matrix 
typedef union mat4{
  float m[16];
  struct{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
  };
} mat4;
//
mat4 mat4_identity();

/// important camera operations
/*
 Calculates an orthographic view matrix using the boundaries of the screen and the zNear
 and zFar clipping distances.
 */
mat4 mat4_ortho(float left, float right, float bottom, float top, float zNear, float zFar);
/*
 Calculates a perspective matrix using the Y-field of view in radians (fovy), the aspect
 ratio of the output window, and the zNear and zFar ends of the frustrum to transform.
 */
mat4 mat4_perspective(float fovy, float aspect, float zNear, float zFar);
/*
 Calculates a view matrix using the positions of the camera (camera), the point to look
 at (lookpt), and the up vector.
 */
mat4 mat4_look_at(vec4 camera, vec4 lookpt, vec4 up);
/// Base matrix operations 
mat4 mat4_add(mat4 left, mat4 right);
mat4 mat4_sub(mat4 left, mat4 right);
mat4 mat4_scalar_mul(mat4 matrix, float scalar);
mat4 mat4_mul(mat4 left, mat4 right);
vec4 mat4_mul_vec4(mat4 left, vec4 right);
vec4 mat4_row(mat4 matrix, size_t rowidx);
vec4 mat4_col(mat4 matrix, size_t colidx);
mat4 mat4_transpose(mat4 matrix);
mat4 mat4_scale_aniso(mat4 matrix, float x, float y, float z); 
mat4 mat4_translate(mat4 matrix, vec4 trans);
float mat4_determinant(mat4 matrix);
///Non-idempodent operations
void mat4_set_identity(mat4*);
void mat4_set_translate(mat4*, vec4);
void mat4_set_add(mat4 *result, mat4 a, mat4);
void mat4_set_sub(mat4 *result,mat4, mat4);
void mat4_set_scalar_mul(mat4 *result,mat4, float);
void mat4_set_mul(mat4 *result,mat4, mat4);
void mat4_set_row(vec4, mat4*, size_t rowidx);
void mat4_set_col(vec4, mat4*, size_t colidx);
void mat4_set_transpose(mat4*, mat4 matrix);
void mat4_set_scale_aniso(mat4 *matrix, float x, float y, float z);
#ifdef _cplusplus
}
#endif
#endif
