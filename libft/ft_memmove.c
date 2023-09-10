/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 01:47:14 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/12/05 09:40:00 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dst;
	s = (const char *)src;
	i = -1;
	if (d < s)
	{
		while (++i < len)
			d[i] = s[i];
	}
	else
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	return (dst);
}
