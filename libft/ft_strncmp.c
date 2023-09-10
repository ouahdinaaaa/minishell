/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:54:55 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/15 14:29:32 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned char		*s_1;
	unsigned char		*s_2;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s_1[i] == s_2[i] && i < n - 1 && s_1[i] != '\0')
		i++;
	return (s_1[i] - s_2[i]);
}

/*
#include <stdio.h>

int main(void)
{
    printf(" res : %d\n", ft_strncmp("coucou", "coucoukaya", 7));
    return(0);
}
*/
