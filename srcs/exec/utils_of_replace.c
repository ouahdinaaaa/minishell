/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:08:42 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/02 13:08:42 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	**double_cut(char *str)
{
	char	**new_str;
	int		k;
	int		tab[2];

	tab[0] = 0;
	tab[1] = 0;
	k = 0;
	new_str = malloc(sizeof(char *) * 3);
	new_str[tab[1]] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[tab[0]] && str[tab[0]] != ' ')
	{
		new_str[tab[1]][tab[0]] = str[tab[0]];
		tab[0] += 1;
	}
	new_str[tab[1]][tab[0]] = '\0';
	tab[1] += 1;
	new_str[tab[1]] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[tab[0]])
	{
		new_str[tab[1]][k] = str[tab[0]];
		tab[0] += 1;
		k++;
	}
	return (new_str[tab[1]][k] = '\0', new_str[tab[1] + 1] = NULL, new_str);
}

char	*ft_replace_status(int status, char *str)
{
	char	*str2;
	char	*num;
	int		i;
	int		j;

	j = 0;
	i = 2;
	num = ft_itoa(status);
	str2 = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(num) + 1));
	while (num[j])
	{
		str2[j] = num[j];
		j++;
	}
	while (str[i])
	{
		str2[j] = str[i];
		i++;
		j++;
	}
	str2[j] = '\0';
	free(num);
	return (str2);
}

char	*ft_strcpy_sp(char *dest, char *src)
{
	char	*d;

	d = dest;
	while (*src != '\0')
		*d++ = *src++;
	*d = '\0';
	free(src);
	return (dest);
}
