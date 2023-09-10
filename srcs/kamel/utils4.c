/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/13 18:17:08 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

// char	*ft_itoa(int nb)
// {
// 	char	*num;
// 	int		len;
// 	int		nbr;

// 	len = 0;
// 	nbr = nb;
// 	if (nbr <= 0)
// 		len = 1;
// 	while (nbr > 0)
// 	{
// 		nbr /= 10;
// 		len++;
// 	}
// 	num = malloc(sizeof(char) * (len + 1));
// 	num[len] = '\0';
// 	len--;
// 	while (len >= 0)
// 	{
// 		num[len] = (nb % 10) + '0';
// 		nb /= 10;
// 		len--;
// 	}
// 	return (num);
// }

char	*createHeredocFiles(int index)
{
	char	*result;
	char	*itoa;

	result = NULL;
	itoa = ft_itoa(index);
	result = ft_strjoin("here_doc", itoa);
	free(itoa);
	return (result);
}

// retourne 1 s'il y a un file

int	checkInfile(char *commande, int debut)
{
	int	i;

	i = debut;
	while (commande[i + 1])
	{
		if (commande[i + 1] == '>')
		{
			printf("\nerreur de syntaxe près du symbole inattendu « > »\n");
			return (0);
		}
		if (commande[i + 1] != ' ')
		{
			return (1);
		}
		i++;
	}
	printf("\nerreur de syntaxe près du symbole inattendu « newline »\n");
	return (0);
}
