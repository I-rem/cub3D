/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:33:58 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 11:13:49 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		p[len] = s1[len];
		len++;
	}
	p[len] = '\0';
	return (p);
}
