/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:20:45 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/07/10 23:23:12 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_pipex(char *s1, char *s2, size_t n, int nb)
{
	size_t	i;

	i = 0;
	if ((n <= 0 || (ft_strlen(s1) != (ft_strlen(s2) - 1))) && nb)
		return (1);
	if (!nb)
	{
		if (ft_strlen(s1) != ft_strlen(s2))
			return (1);
		while ((s1[i] && s2[i]) && s1[i] == s2[i])
			i++;
		return (s1[i] - s2[i]);
	}
	i = 0;
	while (s1[i] == s2[i] && i < n - 1 && nb)
		i++;
	return (s1[i] - s2[i]);
}
