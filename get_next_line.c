/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:33:51 by ikayacio          #+#    #+#             */
/*   Updated: 2022/11/23 12:51:11 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*free_all(char *result, char *stash)
{
	free (result);
	result = NULL;
	free (stash);
	stash = NULL;
	return (NULL);
}

char	*free_stash(char *stash)
{
	free (stash);
	stash = NULL;
	return (NULL);
}

char	*get_result(char *stash, int *i)
{
	char	*result;
	int		j;

	j = 0;
	if (stash == NULL)
		return (NULL);
	else if (stash[*i] == '\0')
		return (free_stash(stash));
	result = (char *)malloc(sizeof(char) * result_len(stash + *i) + 1);
	if (!result)
		return (free_all(result, stash));
	while (stash[*i] != '\0')
	{
		result[j] = stash[*i];
		*i = *i + 1;
		j++;
		if (result[j - 1] == '\n')
			break ;
	}
	result[j] = '\0';
	if (result[0] == '\0')
		return (free_all(result, stash));
	return (result);
}

char	*get_next_line(int fd)
{
	static char			*stash;
	char				buf[BUFFER_SIZE + 1];
	static int			i;
	int					newline;
	int					readbytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	newline = 0;
	while (newline == 0)
	{
		readbytes = read(fd, buf, BUFFER_SIZE);
		if (readbytes > 0)
			buf[readbytes] = '\0';
		else if ((readbytes <= 0 && stash == NULL) || (stash == NULL && i != 0))
			return (NULL);
		else if (stash == NULL && i == 0)
			stash = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		else if (readbytes <= 0 && stash != NULL)
			break ;
		stash = ft_strjoin(stash, buf);
		newline = check_newline(buf);
	}
	return (get_result(stash, &i));
}
