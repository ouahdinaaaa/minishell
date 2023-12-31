/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:35:14 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncp(const char *s1, const char *s2)
{
	size_t			i;
	size_t			n;
	unsigned char	*s_1;
	unsigned char	*s_2;

	n = ft_strlen(s2);
	if (ft_strlen(s1) != n)
		return (1);
	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s_1[i] == s_2[i] && i < n - 1 && s_1[i] != '\0')
		i++;
	return (s_1[i] - s_2[i]);
}
