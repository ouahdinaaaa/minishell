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

int	containsdollarsign(const char *str)
{
	while (*str != '\0')
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

int	countWordsCd(char *commande)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (commande[i])
	{
		if (commande[i] != ' ')
		{
			words++;
			if (commande[i] == '"')
			{
				while (commande[i] != '"' && commande[i])
					i++;
			}
			else
			{
				while (commande[i] != ' ' && commande[i])
					i++;
			}
		}
		else
			i++;
	}
	return (words);
}
