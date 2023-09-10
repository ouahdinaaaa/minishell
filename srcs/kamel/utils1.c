/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/13 18:03:43 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	strncpSpecial(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s_1;
	unsigned char	*s_2;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s_1[i] == s_2[i] && i < n - 1 && s_1[i] != '\0')
		i++;
	return (s_1[i] - s_2[i]);
}

int	skipFirstSpaces(char *commande)
{
	int	index;

	index = 0;
	while (commande[index] == ' ')
		index++;
	return (index);
}

char	*append_char(char *str, char c)
{
	int		len;
	char	*new_str;

	len = strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}
