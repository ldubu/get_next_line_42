#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const*s2)
{
	char	*new_s;
	size_t	size;
	int		i;

	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	new_s = (char *) malloc(sizeof(char) * (size + 1));
	if (!new_s)
		return (NULL);
	while (*s1)
		new_s[i++] = *s1++;
	while (*s2)
		new_s[i++] = *s2++;
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_strrchr(const char *s, int c)
{
	char	a;
	int		b;

	a = (char)c;
	b = 0;
	while (s[b])
		b++;
	if (a == '\0')
		return ((char *)s + b);
	while (--b >= 0)
	{
		if (*s == a)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*cpy;

	len = ft_strlen(s1);
	cpy = NULL;
	cpy = (char *) malloc(sizeof(char) * (len + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (len-- > 0)
		cpy[i++] = *s1++;
	cpy[i] = '\0';
	return (cpy);
}

size_t	ft_strlen(const char *s) //retirer si pas utilisé
{
	size_t	lenght;

	lenght = 0;
	while (*s++)
		lenght++;
	return (lenght);
}