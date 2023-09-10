/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseCommand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/09 22:11:01 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stockage_commande(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].cmd = strcpySpecial(p[ip], '\0', pi, tab);
	free(tab);
}

char	*clear_cmd(char *str)
{
	char	*result;
	char	**new_str;
	int		len;
	int		i;
	int		j;

	i = 0, j = 0;
	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] && (str[i] == '>' || str[i] == '<'))
				i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] && str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
					i++;
				i++;
			}
			else
			{
				while (str[i] && str[i] != ' ')
					i++;
			}
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	new_str = ft_split(result, ' ');
	i = 1;
	while (new_str[i])
	{
		new_str[0] = ft_strjoin(new_str[0], ft_strjoin(" ", new_str[i]));
		i++;
	}
	result = ft_strcpy(result, new_str[0]);
	free_char_double(new_str);
    free(str);
	return (result);
}

void	cmdopt(t_pipex *pipex, int ip, char *str, char **p)
{
	int	i;
	int	size;

	size = ft_strlen(str);
	i = size - 1;
	while (str[i] && str[i] != '>' && i > 0)
	{
		if (str[i] == '"')
		{
			i--;
			while (str[i] != '"')
				i--;
		}
		if (str[i] == '\'')
		{
			i--;
			while (str[i] != '\'')
				i--;
		}
		i--;
	}
	if (str[i] == '>')
	{
		pipex[ip].out = 1;
		if (str[i - 1] == '>')
			i--;	
		pipex[ip].index_char = ft_strlen(p[ip]) - ft_strlen(str) + i;
		outfile(p, pipex, ip);
	}
}
