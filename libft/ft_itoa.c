/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:01:34 by ikayacio          #+#    #+#             */
/*   Updated: 2022/10/15 15:13:17 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		len++;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	handle_min(char *s)
{
	s[0] = '-';
	s[1] = '2';
	s[2] = '1';
	s[3] = '4';
	s[4] = '7';
	s[5] = '4';
	s[6] = '8';
	s[7] = '3';
	s[8] = '6';
	s[9] = '4';
	s[10] = '8';
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = find_len(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	else if (n == -2147483648)
		handle_min(result);
	else if (n == 0)
		result[0] = '0';
	else if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	result[len] = '\0';
	len--;
	while (n > 0)
	{
		result[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (result);
}
