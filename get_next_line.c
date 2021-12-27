/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:13:58 by ldubuche          #+#    #+#             */
/*   Updated: 2021/12/27 15:28:06 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_buffer(char *current_read, char *buffer, int fd);
char	*ft_buffjoin(char *buffer, char *str, char *to_free);
void	fill_retour(char **buffer, int len, char *retour);
char	*r_value(char **buffer, char *current_value);
char	*free_str(char *str);

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*current_read;
	int			len;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	current_read = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!current_read)
		return (NULL);
	len = read(fd, current_read, BUFFER_SIZE);
	if (len < 0)
		return (free_str(current_read));
	current_read[len] = '\0';
	if (len > 0)
	{
		buffer = fill_buffer(current_read, buffer, fd);
		if (buffer == NULL)
			return (free_str(current_read));
	}
	else if (len == 0 && (!buffer || buffer[0] == '\0'))
	{
		free_str(buffer);
		return (free_str(current_read));
	}
	return (r_value(&buffer, current_read));
}

char	*fill_buffer(char *current_read, char *buffer, int fd)
{
	int		len;

	len = 1;
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (free_str(buffer));
	}
	buffer = ft_buffjoin(buffer, current_read, buffer);
	if (!buffer)
		return (NULL);
	while (ft_strrchr(buffer, '\n') == NULL && len != 0)
	{
		len = read(fd, current_read, BUFFER_SIZE);
		if (len < 0)
			return (NULL);
		current_read[len] = '\0';
		buffer = ft_buffjoin(buffer, current_read, buffer);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

char	*r_value(char **buffer, char *current_read)
{
	int		len;
	char	*retour;
	char	*nl_position;

	free_str(current_read);
	nl_position = ft_strrchr(*buffer, '\n');
	if (nl_position)
		len = nl_position - *buffer + 1;
	else
		len = ft_strlen(*buffer);
	retour = (char *) malloc(sizeof(char) * len + 1);
	if (!retour)
		return (free_str(*buffer));
	fill_retour(buffer, len, retour);
	if (nl_position)
		*buffer = ft_buffjoin("", nl_position + 1, *buffer);
	else
		*buffer = ft_buffjoin("", *buffer + len, *buffer);
	if (!(*buffer))
		return (free_str(*buffer));
	return (retour);
}

char	*ft_buffjoin(char *buffer, char *str, char *to_free)
{
	buffer = ft_strjoin(buffer, str);
	if (!buffer)
		return (NULL);
	free(to_free);
	return (buffer);
}

void	fill_retour(char **buffer, int len, char *retour)
{
	int	i;

	i = 0;
	while (len--)
	{
		retour[i] = (*buffer)[i];
		i++;
	}
	retour[i] = '\0';
}
