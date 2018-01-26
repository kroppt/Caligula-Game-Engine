#include "nus/linalg.h"
/**
  NusgartLib Linear Algebra implementation file-- provides an implementation of vectors and matrices
  Copyright 2016 Nicholas Nusgart.
 */
//
vec4 vec4_add(vec4 a, vec4 b){
  return (vec4){ .x=a.x+b.x, .y=a.y+b.y, .z=a.z+b.z,.w=a.w+b.w };
}
//
vec4 vec4_sub(vec4 a, vec4 b){
  return (vec4){ .x=a.x-b.x, .y=a.y-b.y, .z=a.z-b.z,.w=a.w-b.w };
}
//
float vec4_dot(vec4 a, vec4 b){
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
//
vec4 vec4_scalar_mult(vec4 a, float s){
  return (vec4){.x=a.x*s, .y=a.y*s, .z=a.z*s, .w=a.w*s };
}
// is identical to vec3 cross and sets w to 1.0
vec4 vec4_cross(vec4 a, vec4 b){
  return (vec4){.x=a.y*b.z - a.z*b.y, .y=a.x*b.z - b.x*a.z, .z= a.x*b.y - b.x * a.y, 1.0f};
}
//
vec4 vec4_reflect(vec4 a, vec4 b){
  float p = 2.f * vec4_dot(a, b);
  return (vec4){.x= a.x - p*b.x, .y=a.y - p*b.y,.z= a.z - p*b.z, .w=a.w - p*b.w};
}
//
vec4 vec4_project(vec4 a, vec4 b){
  float f =  vec4_dot(a,b)/vec4_dot(b,b);
  return (vec4){.x= f*b.x, .y= f*b.y, .z = f*b.z, .w = f*b.w};
}
//
float vec4_len(vec4 a){
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}
//
vec4 vec4_norm(vec4 a){
  float len = vec4_len(a);
  return (vec4){.x = a.x / len, .y=a.y/len, .z=a.z/len, .w=a.w/len};
}

////Matrix 
// returns an identity matrix
mat4 mat4_identity(){
  return (mat4){.m=
         {1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1} };
}
// returns a+b
mat4 mat4_add(mat4 a, mat4 b){
  mat4 result;
  for(int idx=0; idx < 16; idx++){
    result.m[idx] = a.m[idx] + b.m[idx];
  }
  return result;
}
mat4 mat4_sub(mat4 a, mat4 b){
  mat4 result;
  for(int idx=0; idx < 16; idx++){
    result.m[idx] = a.m[idx] - b.m[idx];
  }
  return result;
}
mat4 mat4_scalar_mul(mat4 a, float b){
  mat4 result;
  for(int idx=0; idx < 16; idx++){
    result.m[idx] = a.m[idx] * b;
  }
  return result;
}
vec4 mat4_mul_vec4(mat4 left, vec4 right){
  return (vec4){ 
    .x = left.m00 * right.x + left.m01 * right.y + left.m02 * right.z + left.m03 * right.w,
    .y = left.m10 * right.x + left.m11 * right.y + left.m12 * right.z + left.m13 * right.w,
    .z = left.m20 * right.x + left.m21 * right.y + left.m22 * right.z + left.m23 * right.w,
    .w = left.m30 * right.x + left.m31 * right.y + left.m32 * right.z + left.m33 * right.w,
  };
}
mat4 mat4_mul(mat4 left, mat4 right){
  return (mat4){
    .m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03,
    .m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03,
    .m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03,
    .m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03,
    .m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13,
    .m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13,
    .m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13,
    .m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13,
    .m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23,
    .m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23,
    .m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23,
    .m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23,
    .m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33,
    .m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33,
    .m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33,
    .m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33
  };
}
vec4 mat4_row(mat4 m, size_t rowidx){
  CONTRACT(rowidx < 3);
  size_t r = rowidx << 2;
  return (vec4){.x=m.m[r],.y=m.m[r+1], .z=m.m[r+2], .w=m.m[r+3]};
}
vec4 mat4_col(mat4 m, size_t colidx){
  CONTRACT(colidx < 3);
  return (vec4){.x =m.m[colidx], .y=m.m[colidx+4], .z=m.m[colidx+8], .w=m.m[colidx+12]};
}
mat4 mat4_transpose(mat4 m){
  return (mat4){.m={
    m.m00, m.m10, m.m20, m.m30,
    m.m01, m.m11, m.m21, m.m31,
    m.m02, m.m12, m.m22, m.m32,
    m.m03, m.m13, m.m23, m.m33,
  }};
}
mat4 mat4_scale_aniso(mat4 m, float x, float y, float z){
  return (mat4){.m={
    m.m00*x, m.m01*x, m.m02*x, m.m03*x,
    m.m10*y, m.m11*y, m.m21*y, m.m13*y,
    m.m20*z, m.m21*z, m.m22*z, m.m23*z,
    m.m30, m.m31, m.m32, m.m33,
  }};
}

float mat4_determinant(mat4 source){
  return (source.m00 * source.m11 - source.m01 * source.m10) * (source.m22 * source.m33 - source.m23 * source.m32) - (source.m00  
    		 * source.m12 - source.m02 * source.m10) * (source.m21 * source.m33 - source.m23 * source.m31)
                 + (source.m00 * source.m13 - source.m03 * source.m10) * (source.m21 * source.m32 - source.m22 * source.m31) + (source.m01 
                 * source.m12 - source.m02 * source.m11) * (source.m20 * source.m33 - source.m23 * source.m30)
                 - (source.m01 * source.m13 - source.m03 * source.m11) * (source.m20 * source.m32 - source.m22 * source.m30) + (source.m02 
                 * source.m13 - source.m03 * source.m12) * (source.m20 * source.m31 - source.m21 * source.m30);
}

mat4 mat4_translate(mat4 mat, vec4 trans){
  mat4 m = mat;
  m.m30 += vec4_dot(mat4_row(mat, 0), trans);
  m.m31 += vec4_dot(mat4_row(mat, 1), trans);
  m.m32 += vec4_dot(mat4_row(mat, 2), trans);
  m.m33 += vec4_dot(mat4_row(mat, 3), trans);
  return m;
}


mat4 mat4_invert(mat4 m){
  float f = mat4_determinant(m);
  if(f == 0)return m;
  f = 1.f/f;
  return (mat4){
  .m00 = (m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) + m.m12 * (m.m23 * m.m31 - m.m21 * m.m33) + m.m13 * (m.m21 * m.m32 - m.m22 * m.m31)) * f,
  .m01 = (m.m21 * (m.m02 * m.m33 - m.m03 * m.m32) + m.m22 * (m.m03 * m.m31 - m.m01 * m.m33) + m.m23 * (m.m01 * m.m32 - m.m02 * m.m31)) * f,
  .m02 = (m.m31 * (m.m02 * m.m13 - m.m03 * m.m12) + m.m32 * (m.m03 * m.m11 - m.m01 * m.m13) + m.m33 * (m.m01 * m.m12 - m.m02 * m.m11)) * f,
  .m03 = (m.m01 * (m.m13 * m.m22 - m.m12 * m.m23) + m.m02 * (m.m11 * m.m23 - m.m13 * m.m21) + m.m03 * (m.m12 * m.m21 - m.m11 * m.m22)) * f,
  .m10 = (m.m12 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m22 * m.m30 - m.m20 * m.m32) + m.m10 * (m.m23 * m.m32 - m.m22 * m.m33)) * f,
  .m11 = (m.m22 * (m.m00 * m.m33 - m.m03 * m.m30) + m.m23 * (m.m02 * m.m30 - m.m00 * m.m32) + m.m20 * (m.m03 * m.m32 - m.m02 * m.m33)) * f,
  .m12 = (m.m32 * (m.m00 * m.m13 - m.m03 * m.m10) + m.m33 * (m.m02 * m.m10 - m.m00 * m.m12) + m.m30 * (m.m03 * m.m12 - m.m02 * m.m13)) * f,
  .m13 = (m.m02 * (m.m13 * m.m20 - m.m10 * m.m23) + m.m03 * (m.m10 * m.m22 - m.m12 * m.m20) + m.m00 * (m.m12 * m.m23 - m.m13 * m.m22)) * f,
  .m20 = (m.m13 * (m.m20 * m.m31 - m.m21 * m.m30) + m.m10 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m11 * (m.m23 * m.m30 - m.m20 * m.m33)) * f,
  .m21 = (m.m23 * (m.m00 * m.m31 - m.m01 * m.m30) + m.m20 * (m.m01 * m.m33 - m.m03 * m.m31) + m.m21 * (m.m03 * m.m30 - m.m00 * m.m33)) * f,
  .m22 = (m.m33 * (m.m00 * m.m11 - m.m01 * m.m10) + m.m30 * (m.m01 * m.m13 - m.m03 * m.m11) + m.m31 * (m.m03 * m.m10 - m.m00 * m.m13)) * f,
  .m23 = (m.m03 * (m.m11 * m.m20 - m.m10 * m.m21) + m.m00 * (m.m13 * m.m21 - m.m11 * m.m23) + m.m01 * (m.m10 * m.m23 - m.m13 * m.m20)) * f,
  .m30 = (m.m10 * (m.m22 * m.m31 - m.m21 * m.m32) + m.m11 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m12 * (m.m21 * m.m30 - m.m20 * m.m31)) * f,
  .m31 = (m.m20 * (m.m02 * m.m31 - m.m01 * m.m32) + m.m21 * (m.m00 * m.m32 - m.m02 * m.m30) + m.m22 * (m.m01 * m.m30 - m.m00 * m.m31)) * f,
  .m32 = (m.m30 * (m.m02 * m.m11 - m.m01 * m.m12) + m.m31 * (m.m00 * m.m12 - m.m02 * m.m10) + m.m32 * (m.m01 * m.m10 - m.m00 * m.m11)) * f,
  .m33 = (m.m00 * (m.m11 * m.m22 - m.m12 * m.m21) + m.m01 * (m.m12 * m.m20 - m.m10 * m.m22) + m.m02 * (m.m10 * m.m21 - m.m11 * m.m20)) * f,
  };
}
///Non-idempodent operations
//
void mat4_set_identity(mat4 *m){
  memset(m->m, 0, sizeof(m->m));
  for(int i = 0; i < 4; i++){
     m->m[(i<<2) + i] = 1;
  }
}

mat4 mat4_ortho(float left, float right, float bottom, float top, float zNear, float zFar){
  mat4 m = {.m={0.f}};
  m.m00 = 2.0f / (right - left);
  m.m11 = 2.0f / (top - bottom);
  m.m22 = (-2.0f) / (zFar - zNear);
  m.m30 = -((right + left) / (right - left));
  m.m31 = -((top + bottom) / (top - bottom));
  m.m32 = -((zFar + zNear) / (zFar - zNear));
  m.m33 = 1.0f;
  return m;
}

mat4 mat4_perspective(float fovy, float aspect, float zNear, float zFar){
  float y_scale = 1.f / tanf(fovy / 2.0f);
  float x_scale = y_scale / aspect;
  float frustrum_length = zFar - zNear;
  mat4 m = {.m={0.f}};
  m.m00 = x_scale;
  m.m11 = y_scale;
  m.m22 = -((zFar + zNear) / frustrum_length);
  m.m23 = -1.0f;
  m.m32 = -((2.0f * zNear * zFar) / frustrum_length);
  return m;
}

mat4 mat4_look_at(vec4 camera, vec4 lookpt, vec4 up){
  vec4 direction = vec4_norm(vec4_sub(camera, lookpt));
  vec4 norm_up = vec4_norm(up);
  vec4 right = vec4_cross(direction, norm_up);
  up = vec4_cross(right, direction);
  return (mat4)
         {.m={right.x, up.x, -direction.x, 0.f,
              right.y, up.y, -direction.y, 0.f,
              right.z, up.z, -direction.z, 0.f,
    -vec4_dot(right,camera), -vec4_dot(up,camera), vec4_dot(camera,camera), 1.0f} };
}

// TODO implement later
void mat4_set_add(mat4 *result, mat4 a, mat4 b){
  for(int idx=0; idx < 16; idx++){
    result->m[idx] = a.m[idx] + b.m[idx];
  }
}
void mat4_set_sub(mat4 *result,mat4 a, mat4 b){
  for(int idx=0; idx < 16; idx++){
    result->m[idx] = a.m[idx] - b.m[idx];
  }
}
void mat4_set_scalar_mul(mat4 *result,mat4 a, float b){
  for(int idx=0; idx < 16; idx++){
    result->m[idx] = a.m[idx] *b;
  }
}
void mat4_set_mul(mat4 *result,mat4 left, mat4 right){
  result->m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03;
  result->m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03;
  result->m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03;
  result->m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03;
  result->m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13;
  result->m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13;
  result->m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13;
  result->m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13;
  result->m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23;
  result->m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23;
  result->m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23;
  result->m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23;
  result->m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33;
  result->m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33;
  result->m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33;
  result->m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33;
}
void mat4_set_row(vec4 a, mat4 *r, size_t rowidx){
  r->m[rowidx*4+0] = a.x;
  r->m[rowidx*4+1] = a.y;
  r->m[rowidx*4+2] = a.z;
  r->m[rowidx*4+3] = a.w;
}
void mat4_set_col(vec4 a, mat4 *r, size_t colidx){
  r->m[colidx+0] = a.x;
  r->m[colidx+4] = a.y;
  r->m[colidx+8] = a.z;
  r->m[colidx+12] = a.w;
}
void mat4_set_transpose(mat4 *res, mat4 m){
  float ab[] = {
    m.m00, m.m10, m.m20, m.m30,
    m.m01, m.m11, m.m21, m.m31,
    m.m02, m.m12, m.m22, m.m32,
    m.m03, m.m13, m.m23, m.m33,
  };
  memcpy(res->m, ab, sizeof(ab));
}
void mat4_set_scale_aniso(mat4 *m, float x, float y, float z){
  float ab[] ={
    m->m00*x, m->m01*x, m->m02*x, m->m03*x,
    m->m10*y, m->m11*y, m->m21*y, m->m13*y,
    m->m20*z, m->m21*z, m->m22*z, m->m23*z,
    m->m30,   m->m31  , m->m32  , m->m33,
  };
  memcpy(m->m, ab, sizeof(ab));
}

void mat4_set_translate(mat4*m, vec4 v){
  mat4_set_identity(m);
  m->m30 = v.x;
  m->m31 = v.y;
  m->m32 = v.z;
}

void mat4_set_rotation(mat4 *m, vec4 v){
  float ab[] = {
    v.x*v.x+v.y*v.y - v.z*v.z - v.w * v.w, 2 * v.y * v.z - 2 * v.x * v.w, 2 * v.y * v.w + 2 * v.x * v.z, 0,
    2 * v.y * v.z + 2 * v.x * v.w , v.x*v.x-v.y*v.y + v.z*v.z - v.w * v.w, 2*v.z * v.w - 2 * v.x * v.y, 0,
    2 * v.y * v.w - 2 * v.x * v.z , 2 * v.z * v.w + 2 * v.x * v.y ,  v.x*v.x-v.y*v.y - v.z*v.z + v.w * v.w, 0,
    0,0,0,1
  };
  memcpy(m->m, ab, sizeof(ab));
}