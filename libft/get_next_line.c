/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:33:51 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 14:43:28 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	int		i;
	int		rd;
	char	character;
	char	*buffer;

	i = 0;
	rd = 0;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(100000);
	rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
	while (rd > 0)
	{
		buffer[i++] = character;
		if (character == '\n')
			break ;
		rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
	}
	buffer[i] = '\0';
	if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
		return (free(buffer), NULL);
	return (buffer);
}
