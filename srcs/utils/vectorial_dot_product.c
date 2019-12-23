#include "../../includes/scope.h"

int       dot_vec2i(t_vec2i vec1, t_vec2i vec2)
{
  int     ret;

  ret = vec1.x * vec2.x + vec1.y * vec2.y;
  return ret;
}

double    dot_vec2f(t_vec2f vec1, t_vec2f vec2)
{
  double  ret;

  ret = vec1.x * vec2.x + vec1.y * vec2.y;
  return ret;
}

int       dot_vec3i(t_vec3i vec1, t_vec3i vec2)
{
  int     ret;

  ret = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
  return ret;
}

double    dot_vec3f(t_vec3f vec1, t_vec3f vec2)
{
  double  ret;

  ret = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
  return ret;
}
