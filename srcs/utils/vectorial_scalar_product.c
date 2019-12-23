#include "../../includes/scope.h"

t_vec2i   scal_vec2i(t_vec2i vec, int scalar)
{
  t_vec2i ret;

  ret.x = vec.x * scalar;
  ret.y = vec.y * scalar;
  return ret;
}

t_vec2f   scal_vec2f(t_vec2f vec, double scalar)
{
  t_vec2f ret;

  ret.x = vec.x * scalar;
  ret.y = vec.y * scalar;
  return ret;
}

t_vec3i   scal_vec3i(t_vec3i vec, int scalar)
{
  t_vec3i ret;

  ret.x = vec.x * scalar;
  ret.y = vec.y * scalar;
  ret.z = vec.z * scalar;
  return ret;
}

t_vec3f   scal_vec3f(t_vec3f vec, double scalar)
{
  t_vec3f ret;

  ret.x = vec.x * scalar;
  ret.y = vec.y * scalar;
  ret.z = vec.z * scalar;
  return ret;
}
