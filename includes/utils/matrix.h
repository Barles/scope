#ifndef MATRIX_H
# define MATRIX_H

typedef struct    s_mat4i
{
  int             m00;
  int             m01;
  int             m02;
  int             m03;
  int             m10;
  int             m11;
  int             m12;
  int             m13;
  int             m20;
  int             m21;
  int             m22;
  int             m23;
  int             m30;
  int             m31;
  int             m32;
  int             m33;
}                 t_mat4i;

typedef struct    s_mat4f
{
  double          m00;
  double          m01;
  double          m02;
  double          m03;
  double          m10;
  double          m11;
  double          m12;
  double          m13;
  double          m20;
  double          m21;
  double          m22;
  double          m23;
  double          m30;
  double          m31;
  double          m32;
  double          m33;
}                 t_mat4f;

/*
**  utils/matrix.c
*/


#endif
