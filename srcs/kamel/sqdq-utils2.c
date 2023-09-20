/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqdq-utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:35:01 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*strjoinExtremites(char *str, char c)
{
	size_t	length;
	char	*nouvelleChaine;

	length = ft_strlen(str);
	nouvelleChaine = (char *)malloc((length + 3) * sizeof(char));
	nouvelleChaine[0] = c;
	strcpy(nouvelleChaine + 1, str);
	nouvelleChaine[length + 1] = c;
	nouvelleChaine[length + 2] = '\0';
	free(str);
	return (nouvelleChaine);
}

char	*putQuotes(char *str)
{
	if (isThereChar(str, ' '))
	{
		if (isThereChar(str, '"'))
			str = strjoinExtremites(str, '\'');
		else if (isThereChar(str, '\''))
			str = strjoinExtremites(str, '"');
		else
			str = strjoinExtremites(str, '"');
	}
	return (str);
}

char	**quotes(char *str)
{
	char	**mots;
	int		i;

	if (str == NULL)
		return (NULL);
	i = 0;
	mots = words(str);
	while (i < ft_countwords(str))
	{
		mots[i] = putQuotes(mots[i]);
		i++;
	}
	return (mots);
}

char	*collerMots(char **mots, int taille)
{
	int		i;
	char	*resultat;
	int		tailleTotale;

	i = 0;
	if (taille <= 0)
		return (NULL);
	tailleTotale = 0;
	while (i < taille)
	{
		tailleTotale += ft_strlen(mots[i]);
		i++;
	}
	tailleTotale += taille - 1;
	resultat = (char *)malloc((tailleTotale + 1) * sizeof(char));
	resultat[0] = '\0';
	i = 0;
	while (i < taille)
	{
		ft_strcat(resultat, mots[i]);
		if (i < taille - 1)
			ft_strcat(resultat, " ");
		i++;
	}
	return (resultat);
}
