#include "../../includes/scope.h"

float stof(const char* s){
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1;
      continue;
    };
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };
  };
  return rez * fact;
};

int   load_obj(const char *file, t_vec3f **vert, t_vec2f **uv, t_vec3f **norm)
{
  unsigned int  *vert_i;
  unsigned int  *uv_i;
  unsigned int  *norm_i;
  t_vec3f       *temp_vert;
  t_vec2f       *temp_uv;
  t_vec3f       *temp_norm;
  int           fd;
  int           vert_index;
  int           uv_index;
  int           norm_index;
  int           face_index;
  char          *line;

  vert_index = 0;
  uv_index = 0;
  norm_index = 0;
  face_index = 0;
  temp_vert = malloc(sizeof(t_vec3f));
  temp_uv = malloc(sizeof(t_vec2f));
  temp_norm = malloc(sizeof(t_vec3f));
  vert_i = NULL;
  // vert_i = malloc(sizeof(unsigned int) * 3);
  uv_i = malloc(sizeof(unsigned int) * 3);
  norm_i = malloc(sizeof(unsigned int) * 3);
  fd = open(file, O_RDONLY);
  while (get_next_line(fd, &line) > 0)
  {
    if (ft_strncmp(line, "v ", 2) == 0)
    {
      parse_vert(line, &temp_vert, vert_index);
      // printf("vec -> x: %f, y: %f, z: %f\n", temp_vert[vert_index].x, temp_vert[vert_index].y, temp_vert[vert_index].z);
      vert_index++;
    }
    else if (ft_strncmp(line, "vt ", 3) == 0)
    {
      parse_uv(line, &temp_uv, uv_index);
      // printf("vec -> x: %f, y: %f\n", temp_uv[uv_index].x, temp_uv[uv_index].y);
      uv_index++;
    }
    else if (ft_strncmp(line, "vn ", 3) == 0)
    {
      parse_norm(line, &temp_norm, norm_index);
      norm_index++;
    }
    else if (ft_strncmp(line, "f ", 2) == 0)
    {
      // vert_i = realloc(*vert_i, sizeof(unsigned int) * (face_index + 3));

      unsigned int  *temp_v;
      unsigned int  *temp_u;
      unsigned int  *temp_n;
      char          **split;
      char          ***subsplit;

      split = ft_strsplit(line, ' ');
      subsplit = malloc(sizeof(char *) * 3);

      // printf("FaceIndex: %d\n", face_index);

      subsplit[0] = ft_strsplit(split[1], '/');
      subsplit[1] = ft_strsplit(split[2], '/');
      subsplit[2] = ft_strsplit(split[3], '/');

      temp_v = malloc(sizeof(unsigned int) * (face_index + 3));
      int i = 0;
      while (i < face_index)
      {
        temp_v[i] = vert_i[i];
        // if (i < 1)
        //   printf("faceindex: %d, i: %d, temp_v: %d, *v: %d\n", face_index, i, temp_v[i], vert_i[i]);
        i++;
      }

      if (vert_i != NULL)
        free(vert_i);

      temp_v[face_index] = (unsigned int) ft_atoi(subsplit[0][0]);
      temp_v[face_index+1] = (unsigned int) ft_atoi(subsplit[1][0]);
      temp_v[face_index+2] = (unsigned int) ft_atoi(subsplit[2][0]);

      free(subsplit);
      vert_i = malloc(sizeof(unsigned int) * (face_index + 3));

      i = 0;
      while (i < face_index + 3)
      {
        vert_i[i] = temp_v[i];
        // printf("i: %d, temp_v: %d, *v: %d\n", i, temp_v[i], vert_i[i]);
        i++;
      }

      free(temp_v);

      // parse_face(line, &vert_i, &uv_i, &norm_i, face_index);
      face_index += 3;
    }
  }


  int j = 0;
  // while (j < face_index){
  //   // printf("j: %d, %d\n", j, vert_i[j]);
  //   j++;
  // }
  // // while (vert_i[i])
  while (j <= 15)
  {
    printf("i->%d\n", j);
    t_vec3f *out_v_temp = NULL;
    //
    out_v_temp = malloc(sizeof(t_vec3f) * (j + 1));
    out_v_temp = *vert;
    unsigned int vertexIndex = vert_i[j];
    //
    // printf("vertIndex: %d\n", vertexIndex);
    t_vec3f vertex = temp_vert[vertexIndex-1];
    // out_v_temp[j] = vertex;
    *vert = malloc(sizeof(out_v_temp));
    *vert = out_v_temp;

    // free(out_v_temp);
    j++;
  }
  printf("test\n");

  // while (i < uv_index)
  // {
  //   printf("uv   n° %d -> x: %f, y: %f\n", i, temp_uv[i].x, temp_uv[i].y);
  //   i++;
  // }
  // i = 0;
  // while (i < vert_index)
  // {
  //   printf("vert n° %d -> x: %f, y: %f, z: %f\n", i, temp_vert[i].x, temp_vert[i].y, temp_vert[i].z);
  //   i++;
  // }
  // i = 0;
  // while (i < norm_index)
  // {
  //   printf("norm n° %d -> x: %f, y: %f, z: %f\n", i, temp_norm[i].x, temp_norm[i].y, temp_norm[i].z);
  //   i++;
  // }
  close(fd);
  printf("test\n");
  free(line);
  return 1;
}

void parse_vert(char *s, t_vec3f **vert, int index)
{
  t_vec3f *temp;
  float   x;
  float   y;
  float   z;
  char    **split;

  temp = malloc(sizeof(t_vec3f) * (index + 1));
  temp = *vert;
  split = ft_strsplit(s, ' ');
  x = stof(split[1]);
  y = stof(split[2]);
  z = stof(split[3]);
  temp[index] = c_vec3f(x, y, z);
  free(*vert);
  *vert = malloc(sizeof(temp));
  *vert = temp;
  free(temp);
}

void parse_uv(char *s, t_vec2f **uvs, int index)
{
  t_vec2f *temp;
  float   x;
  float   y;
  char    **split;

  temp = malloc(sizeof(t_vec2f) * (index + 1));
  temp = *uvs;
  split = ft_strsplit(s, ' ');
  x = stof(split[1]);
  y = stof(split[2]);
  temp[index] = c_vec2f(x, y);
  free(*uvs);
  *uvs = malloc(sizeof(temp));
  *uvs = temp;
  free(temp);
}

void parse_norm(char *s, t_vec3f **norm, int index)
{
  t_vec3f *temp;
  float   x;
  float   y;
  float   z;
  char    **split;

  temp = malloc(sizeof(t_vec3f) * (index + 1));
  temp = *norm;
  split = ft_strsplit(s, ' ');
  x = stof(split[1]);
  y = stof(split[2]);
  z = stof(split[3]);
  // printf("index:%d, x:%f, y:%f, z:%f\n", index, x, y, z);
  temp[index] = c_vec3f(x, y, z);
  free(*norm);
  *norm = malloc(sizeof(temp));
  *norm = temp;
  free(temp);
}

void parse_face(char *s, unsigned int **v, unsigned int **u, unsigned int **n, int index)
{
  unsigned int  *temp_v;
  unsigned int  *temp_u;
  unsigned int  *temp_n;
  char          **split;
  char          ***subsplit;

  split = ft_strsplit(s, ' ');
  subsplit = malloc(sizeof(char *) * 3);

  subsplit[0] = ft_strsplit(split[1], '/');
  subsplit[1] = ft_strsplit(split[2], '/');
  subsplit[2] = ft_strsplit(split[3], '/');
  printf("SPLIT     -> [1]    %s, [2]    %s, [3]    %s\n", split[1], split[2], split[3]);
  printf("SUBSPLIT  -> [0][0] %d, [0][1] %s, [0][2] %s\n", (unsigned int)ft_atoi(subsplit[0][0]), subsplit[0][1], subsplit[0][2]);
  printf("SUBSPLIT  -> [1][0] %s, [1][1] %s, [1][2] %s\n", subsplit[1][0], subsplit[1][1], subsplit[1][2]);
  printf("SUBSPLIT  -> [2][0] %s, [2][1] %s, [2][2] %s\n", subsplit[2][0], subsplit[2][1], subsplit[2][2]);

  temp_v = malloc(sizeof(unsigned int) * (index + 3));
  int i = 0;
  // printf("test\n");
  while (i < index)
  {
    temp_v[i] = *v[i];
    printf("i: %d, temp_v: %d, *v: %d\n", i, temp_v[i], *v[i]);
    i++;
  }
  // temp_u = malloc(sizeof(unsigned int) * (index + 3));
  // temp_u = *u;
  // temp_n = malloc(sizeof(unsigned int) * (index + 3));
  // temp_n = *n;

  temp_v[index] = (unsigned int) ft_atoi(subsplit[0][0]);
  temp_v[index+1] = (unsigned int) ft_atoi(subsplit[1][0]);
  temp_v[index+2] = (unsigned int) ft_atoi(subsplit[2][0]);

  // temp_u[index] = (unsigned int) ft_atoi(subsplit[0][1]);
  // temp_u[index+1] = (unsigned int) ft_atoi(subsplit[1][1]);
  // temp_u[index+2] = (unsigned int) ft_atoi(subsplit[2][1]);
  //
  // temp_n[index] = (unsigned int) ft_atoi(subsplit[0][2]);
  // temp_n[index+1] = (unsigned int) ft_atoi(subsplit[1][2]);
  // temp_n[index+2] = (unsigned int) ft_atoi(subsplit[2][2]);


  free(*v);
  // free(*u);
  // free(*n);
  // ft_memdel(*v);
  // *v = ft_memalloc(index + 3);
  // *v = ft_memcpy(*v, temp_v, index + 3);
  // *v = malloc(sizeof(unsigned int) * (index *3));
  // *v = malloc(sizeof(temp_v));
  *v = malloc(sizeof(unsigned int) * (index + 3));
  i = 0;
  printf("test\n");

  while (i < index + 3)
  {
    printf("i: %d, temp_v: %d\n", i, temp_v[i]);
    i++;
  }
  printf("test\n");
  i = 0;
  while (i < index + 3)
  {
    *v[i] = temp_v[i];
    printf("i: %d, temp_v: %d, *v: %d\n", i, temp_v[i], *v[i]);
    i++;
  }
  printf("test\n");
  printf("Index: %d, temp_v: [%d][%d][%d]\n", index, temp_v[index], temp_v[index+1], temp_v[index+2]);
  printf("Index: %d,      v: [%d][%d][%d]\n", index, *v[index], *v[index+1], *v[index+2]);
  // *u = malloc(sizeof(temp_u));
  // *u = temp_u;
  // *n = malloc(sizeof(temp_n));
  // *n = temp_n;
  free(subsplit);
  free(split);
  free(temp_v);
  // free(temp_u);
  // free(temp_n);
}
