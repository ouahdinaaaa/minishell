/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitPipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/08 12:12:40 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

int	countPipes(char *s)
{
	int	i;
	int	nb_pipes;

	nb_pipes = 0;
	i = 0;
	while (s[i])
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
			while (s[i] != '\'')
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

	// printf("\nChaine de caractères : %s\n", s);
	split = malloc((countPipes(s) + 1) * sizeof(char *));
    // printf("\nNombre de pipes : %d\n", countPipes(s));
    if (!s || !(split))
		return (0);
    i = 0;
	j = 0;
	index = 0;
    while (i <= ft_strlen(s))
	{
		if (s[i] == '"')
			while(s[++i] && s[i] != '"')
				i = i;
		else if (s[i] == '\'')
			while(s[++i] && s[i] != '\'')
				i = i;
		else if (s[i] == '|')
		{
			split[j++] = word_dup(s, index, i);
			index = i + 1;
		}
		i++;
	}
	split[j++] = word_dup(s, index, i);
	split[j] = NULL;
    // printf("\n\npipe[0] : [%s]\n", split[0]);
    // printf("pipe[1] : [%s]\n", split[1]);
	return (split);
}
