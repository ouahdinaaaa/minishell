/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:46:22 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/18 14:56:26 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		destlen;

	destlen = ft_strlen(dst);
	i = destlen;
	if (size == 0)
		return (ft_strlen(src));
	if (size < destlen)
		return (size + ft_strlen(src));
	j = 0;
	if (size > i)
	{
		while (src[j] && size - i > 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	while (src[j] != '\0')
		j++;
	return (destlen + j);
}
