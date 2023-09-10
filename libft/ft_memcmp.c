/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:41:45 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/18 14:07:50 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*s1bis;
	char	*s2bis;

	i = 0;
	s1bis = (char *) s1;
	s2bis = (char *) s2;
	while (i < n)
	{
		if (s1bis[i] != s2bis[i])
			return ((unsigned char)s1bis[i] - (unsigned char)s2bis[i]);
		i++;
	}
	return (0);
}
