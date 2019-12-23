#ifndef VECTOR_H
# define VECTOR_H

typedef struct    s_vec2i
{
  int             x;
  int             y;
}                 t_vec2i;

typedef struct    s_vec2f
{
  float           x;
  float           y;
}                 t_vec2f;

typedef struct    s_vec3i
{
  int             x;
  int             y;
  int             z;
}                 t_vec3i;

typedef struct    s_vec3f
{
  float           x;
  float           y;
  float           z;
}                 t_vec3f;

/*
**  utils/vector.c
*/

t_vec2i           c_vec2i(int x, int y);
t_vec2f           c_vec2f(float x, float y);
t_vec3i           c_vec3i(int x, int y, int z);
t_vec3f           c_vec3f(float x, float y, float z);

/*
**  utils/vectorial_addition.c
*/

t_vec2i           a_vec2i(t_vec2i vec1, t_vec2i vec2);
t_vec2f           a_vec2f(t_vec2f vec1, t_vec2f vec2);
t_vec3i           a_vec3i(t_vec3i vec1, t_vec3i vec2);
t_vec3f           a_vec3f(t_vec3f vec1, t_vec3f vec2);

/*
**  utils/vectorial_substraction.c
*/

t_vec2i           s_vec2i(t_vec2i vec1, t_vec2i vec2);
t_vec2f           s_vec2f(t_vec2f vec1, t_vec2f vec2);
t_vec3i           s_vec3i(t_vec3i vec1, t_vec3i vec2);
t_vec3f           s_vec3f(t_vec3f vec1, t_vec3f vec2);

/*
**  utils/vectorial_scalar_product.c
*/

t_vec2i           scal_vec2i(t_vec2i vec, int scalar);
t_vec2f           scal_vec2f(t_vec2f vec, double scalar);
t_vec3i           scal_vec3i(t_vec3i vec, int scalar);
t_vec3f           scal_vec3f(t_vec3f vec, double scalar);

/*
**  utils/vectorial_dot_product.c
*/

int               dot_vec2i(t_vec2i vec1, t_vec2i vec2);
double            dot_vec2f(t_vec2f vec1, t_vec2f vec2);
int               dot_vec3i(t_vec3i vec1, t_vec3i vec2);
double            dot_vec3f(t_vec3f vec1, t_vec3f vec2);

#endif
