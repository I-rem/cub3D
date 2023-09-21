/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:54:06 by ikayacio          #+#    #+#             */
/*   Updated: 2022/10/12 14:46:17 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;	
	char	*source;
	char	*dest;

	source = (char *)src;
	dest = (char *)dst;
	i = 0;
	if (dst == src)
		return (dst);
	if (dst < src)
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
		return (dst);
	}
	while (len--)
		dest[len] = source[len];
	return (dst);
}
