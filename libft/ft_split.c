/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:54:39 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 11:19:57 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**free_words(char **result, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (result[i])
			free(result[i]);
		result[i] = NULL;
		i++;
	}
	if (result)
		free(result);
	result = NULL;
	return (NULL);
}

static char	*make_word(const char *s, char c)
{
	char	*word;
	size_t	i;
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	word = (char *)ft_calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split2(char **result, int i)
{
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (s)
		result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!s || !result)
		return (NULL);
	i = -1;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0' && *s != c)
		{
			result[++i] = make_word(s, c);
			if (!result[i])
			{
				free_words(result, i);
				return (NULL);
			}
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (ft_split2(result, ++i));
}
