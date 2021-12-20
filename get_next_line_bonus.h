#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef FD_MAX
#  define FD_MAX 256 //rechercher pk 256 !!!
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 //se renseigner si on ne donne pas de buffer size si on est sensé en mettre une part défault ou non
# endif

char	*ft_strjoin(char const *s1, char const*s2);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);

#endif