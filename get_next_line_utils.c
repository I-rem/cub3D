/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:32:41 by ikayacio          #+#    #+#             */
/*   Updated: 2023/05/11 17:05:09 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	result_len(char *stash)
{
	int	len;

	len = 0;
	while (stash[len] != '\n' && stash[len] != '\0')
		len++;
	if (stash[len] == '\n')
		len++;
	return (len);
}

int	ft_strlen(char *stash)
{
	int	len;

	len = 0;
	while (stash[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	int		len;

	len = ft_strlen(s1);
	p = (char *) malloc(len + 1);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		s1 = ft_strdup("\0");
	if (s2 == NULL)
		s2 = ft_strdup("\0");
	joined = malloc(sizeof(char) * (ft_strlen((char *)s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

int	check_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (1);
	else
		return (0);
}