#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 5
# define CHECKMALLOC(x) if (!x) return (-1);
# define NBFD 5000

# include <fcntl.h>
# include "libft.h"

int		ft_mycpy(char **dst, char *src);
int		get_next_line(int fd, char **file);

#endif
