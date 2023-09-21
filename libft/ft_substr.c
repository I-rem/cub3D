/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:09:11 by ikayacio          #+#    #+#             */
/*   Updated: 2022/10/15 18:39:04 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
	{
		substr = malloc(sizeof(char) * 1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len <= ft_strlen(s))
		substr = malloc(sizeof(char) * (len + 1));
	else
		substr = malloc(sizeof(char) *(ft_strlen(s) + 1));
	if (!substr)
		return (NULL);
	while ((char)s[start] != '\0' && i < len)
		substr[i++] = (char)s[start++];
	substr[i] = '\0';
	return (substr);
}
