/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:46:05 by ikayacio          #+#    #+#             */
/*   Updated: 2022/10/15 15:58:50 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*source;

	source = (char *)src;
	i = 0;
	while (i < size && dst[i] != '\0')
		i++;
	if (i == size)
		return (i + ft_strlen(src));
	j = 0;
	while (source[j] != '\0')
	{
		if (j < size - i - 1)
			dst[i + j] = source[j];
		j++;
	}
	dst[i + j] = 0;
	return (j + i);
}
