#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

/*
**  loaders/obj_parser.c
*/

int   load_obj(const char *file, t_vec3f **vert, t_vec2f **uv, t_vec3f **norm);
void  parse_vert(char *s, t_vec3f **vert, int index);
void  parse_uv(char *s, t_vec2f **uv, int index);
void  parse_norm(char *s, t_vec3f **norm, int index);
void  parse_face(char *s, unsigned int **v, unsigned int **u, unsigned int **n, int index);

#endif
