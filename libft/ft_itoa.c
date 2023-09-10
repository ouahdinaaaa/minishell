/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:09:35 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/21 19:05:03 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(int n, int len, int sign)
{
	char			*str;
	unsigned int	x;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (sign)
	{
		*str = '-';
		x = -n;
	}
	else
		x = n;
	str[len] = '\0';
	len--;
	while (len >= sign)
	{
		str[len] = (x % 10) + 48;
		x = x / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		temp;
	int		sign;

	len = 0;
	sign = 0;
	if (n < 0)
	{
		len++;
		sign++;
	}
	temp = n;
	while (temp != 0)
	{
		temp = temp / 10;
		len++;
	}
	if (n == 0)
		len++;
	return (ft_convert(n, len, sign));
}
