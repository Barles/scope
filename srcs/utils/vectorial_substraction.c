#include "../../includes/scope.h"

t_vec2i   s_vec2i(t_vec2i vec1, t_vec2i vec2)
{
  t_vec2i ret;

  ret.x = vec1.x - vec2.x;
  ret.y = vec1.y - vec2.y;
  return ret;
}

t_vec2f   s_vec2f(t_vec2f vec1, t_vec2f vec2)
{
  t_vec2f ret;

  ret.x = vec1.x - vec2.x;
  ret.y = vec1.y - vec2.y;
  return ret;
}

t_vec3i   s_vec3i(t_vec3i vec1, t_vec3i vec2)
{
  t_vec3i ret;

  ret.x = vec1.x - vec2.x;
  ret.y = vec1.y - vec2.y;
  ret.z = vec1.z - vec2.z;
  return ret;
}

t_vec3f   s_vec3f(t_vec3f vec1, t_vec3f vec2)
{
  t_vec3f ret;

  ret.x = vec1.x - vec2.x;
  ret.y = vec1.y - vec2.y;
  ret.z = vec1.z - vec2.z;
  return ret;
}
