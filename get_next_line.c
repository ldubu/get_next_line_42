/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:13:58 by ldubuche          #+#    #+#             */
/*   Updated: 2021/12/27 13:28:18 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_buffer(char *current_read, char *buffer, int fd);
char	*ft_buffjoin(char *buffer, char *str, char *to_free);
char	*r_value(char **buffer);
char	*free_str(char *str);

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*current_read;
	int			len;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0) //gestion d'erreur d'input
		return (NULL);
	current_read = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1)); //allocation current read
	if (!current_read)
		return (NULL);
	len = read(fd, current_read, BUFFER_SIZE); //on lit la premiere ligne
	printf("len = %d\n", len);
	if (len < 0)
		return (free_str(current_read));
	current_read[len] = '\0';
	if (len > 0) //si len > 0, on a lu quelque chose, on appelle alors la fonction pur remplir le buffer
	{
		buffer = fill_buffer(current_read, buffer, fd);
		if (buffer == NULL)
			return (free_str(current_read));
	}
	else if (len == 0 && (!buffer || buffer[0] == '\0')) //si on ne lit rien et qu'on est a la fin du buffer on retourne NULL
	{
		printf("good condition enter\n");
		free_str(buffer);
		return (free_str(current_read));
	}
	free_str(current_read); //on free current_read
	return (r_value(&buffer)); //fonction qui creer la chaine que l'on retourne et qui la supprime du buffer
}

char	*fill_buffer(char *current_read, char *buffer, int fd)
{
	int		len;

	len = 1;
	if (!buffer) //a la premiere lecture, on alloue une chaine vide au buffer
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (free_str(buffer));
	}
	buffer = ft_buffjoin(buffer, current_read, buffer); //dans le cas ou il y a deja un \n dans buffer pour ne pas perdre current read
		if (!buffer)
			return (NULL);
	while (ft_strrchr(buffer, '\n') == NULL && len != 0) //tant que il n'y a pas de \n dans buffer ou qu'on a pas atteint la fin du fichier
	{
		len = read(fd, current_read, BUFFER_SIZE); //on lit 
		if (len < 0)
			return (NULL);
		current_read[len] = '\0';
		buffer = ft_buffjoin(buffer, current_read, buffer); //on join buffer et la string qu'on a lu (la fonction free l'ancien buffer)
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

char	*r_value(char **buffer)
{
	int		len;
	char	*retour;
	char	*nl_position;
	int		i;

	nl_position = ft_strrchr(*buffer, '\n'); //on cherche si \n est dans buffer
	if (nl_position)
		len = nl_position - *buffer + 1; //si oui la taille de la string retour et la diff entrele debut et la position de \n
	else
		len = ft_strlen(*buffer); // si non len c'est la taille de buffer
	retour = (char *) malloc(sizeof(char) * len + 1); //on alloue retour
	if (!retour)
		return (free_str(*buffer));
	i = 0; 
	while (len--) //on copie la string dans retour
	{
		retour[i] = (*buffer)[i];
		i++;
	}
	retour[i] = '\0';
	if (nl_position)
		*buffer = ft_buffjoin("", nl_position + 1, *buffer); //s'il rete des choses dans buffer alloue une nouvelle string sans la chaine dans retour
	else
		*buffer = ft_buffjoin("", *buffer + i, *buffer); //si non alloue un \0 globalement 
	if (!(*buffer))
		return (free_str(*buffer));
	return (retour);
}

char	*ft_buffjoin(char *buffer, char *str, char *to_free)
{
	buffer = ft_strjoin(buffer, str);//on alloue la string jointe a buffer
	if (!buffer)
		return (NULL);
	free(to_free); // on free le buffer
	return (buffer);
}

char	*free_str(char *str)//sert a gagner de la place sur les retour erreur
{
	printf("enter free\n");
	if (str != NULL)
	{
		printf("not null\n");
		free(str);
		str = NULL;
	}
	return (NULL);
}
