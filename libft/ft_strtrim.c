/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:46:18 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/23 14:51:49 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Vérifie si dans une chaine de caractère set il y a le caractère c
// Retourne 1 si set contient c
// Retourne 0 si set ne contient pas c

static int	ft_check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

// Cette fonction sert à incrémenter le pointeur vers le début sans le set et
// décrémenter le pointeur vers la fin sans le set
// En commançant du début :
// Tant que le caractère dans la chaine est un set, on avance
// En commançant par la fin :
// Tant que le caractère dans la chaine est un set, on recule

void	ft_limites(char const *s1, char const *set, size_t *debut, size_t *fin)
{
	size_t	len;

	len = ft_strlen((const char *)s1);
	while (ft_check_set(s1[*debut], set) == 1 && s1[*debut])
		*debut = *debut + (long unsigned)1;
	len = len - 1;
	while (ft_check_set(s1[len], set) == 1 && s1[len])
		len--;
	*fin = (long unsigned)len;
}

// Alloue avec malloc et retourne une copie de la chaine de caractères donnée 
// en argument, sans les caractères spécifiés dans le set donné en argument au 
// début et à la fin de la chaine de caractères.

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	debut;
	size_t	fin;
	size_t	len;
	size_t	i;
	char	*resultat;

	debut = 0;
	fin = 0;
	ft_limites(s1, set, &debut, &fin);
	if (debut > fin || debut == ft_strlen(s1))
		len = 0;
	else
		len = fin - debut + 1;
	resultat = (char *)malloc(sizeof(char) * (len + 1));
	if (!resultat)
		return (NULL);
	i = 0;
	while (i <= (fin - debut) && fin != (long unsigned)-1)
	{
		resultat[i] = (s1)[debut + i];
		i++;
	}
	resultat[i] = '\0';
	return (resultat);
}
