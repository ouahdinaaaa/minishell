/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitPipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:34:51 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_pipes(char *s)
{
	size_t	i;
	int	nb_pipes;

	nb_pipes = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '|')
			nb_pipes++;
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			i++;
			if (s[i] && s[i] != ' ')
			{
				i++;
				while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
					i++;
			}
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] && s[i] != ' ')
			{
				i++;
				while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
					i++;
			}
		}
		i++;
	}
	return (nb_pipes);
}

char    **splitPipes(char *s)
{
    size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((ft_count_pipes(s) + 2) * sizeof(char *));
    if (!s || !(split))
		return (0);
    i = 0;
	j = 0;
	index = 0;
    while (i <= ft_strlen(s))
	{
		if (s[i] == '"')
			while(s[++i] && s[i] != '"')
				i = i + 1 - 1;
		else if (s[i] == '\'')
			while(s[++i] && s[i] != '\'')
				i = i + 1 - 1;
		else if (s[i] == '|')
		{
			split[j++] = word_dup(s, index, i);
			index = i + 1;
		}
		i++;
	}
	split[j++] = word_dup(s, index, i);
	split[j] = NULL;
	return (split);
}
