/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:35:33 by ikayacio          #+#    #+#             */
/*   Updated: 2022/10/19 08:23:10 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trimmed;
	size_t		start;
	size_t		len;
	size_t		i;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && in_set(s1[start], set) == 1)
		start++;
	len = ft_strlen(s1);
	while (len > start && in_set(s1[len - 1], set) == 1)
		len--;
	trimmed = malloc(sizeof(char) * (len - start + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start + i < len)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
