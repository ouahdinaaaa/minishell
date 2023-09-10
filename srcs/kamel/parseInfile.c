/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/13 18:17:08 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
void	infile(char **p, t_pipex *pi, int ip)
{
	if (checkInfile(p[ip], pi[ip].index_char) == 0)
	{
		pi[ip].erreur = 1;
		return ;
	}
	if (p[ip][pi[ip].index_char + 1] == '<')
	{
		if (checkFileHeredoc(p[ip], pi[ip].index_char + 1) == 0)
		{
			pi[ip].erreur = 1;
			return ;
		}
		infileHeredoc(p, pi, ip);
	}
	else if (p[ip][pi[ip].index_char + 1] == ' ')
		infileSpaceFile(p, pi, ip);
	else if (p[ip][pi[ip].index_char + 1] == '"')
		infileSpaceDq(p, pi, ip);
	else if (p[ip][pi[ip].index_char + 1] == '\'')
		infileSpaceSq(p, pi, ip);
	else
		infileFile(p, pi, ip);
}

void	infileSpaceFile(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	while (p[ip][pi[ip].index_char + 2] == ' ')
		pi[ip].index_char = pi[ip].index_char + 1;
	if (p[ip][pi[ip].index_char + 2] == '"')
	{
		pi[ip].index_char = pi[ip].index_char + 3;
		pi[ip].in = 1;
		tab = malloc(sizeof(int) * 2);
		tab[0] = pi[ip].index_char;
		tab[1] = ip;
		pi[ip].files[0] = strcpySpecialDq(p[ip], pi, tab);
		pi[ip].index_char = pi[ip].index_char + 1;
		free(tab);
	}
	else if (p[ip][pi[ip].index_char + 2] == '\'')
	{
		pi[ip].index_char = pi[ip].index_char + 3;
		pi[ip].in = 1;
		tab = malloc(sizeof(int) * 2);
		tab[0] = pi[ip].index_char;
		tab[1] = ip;
		pi[ip].files[0] = strcpySpecialSq(p[ip], pi, tab);
		pi[ip].index_char = pi[ip].index_char + 1;
		free(tab);
	}
	else
	{
		pi[ip].index_char = pi[ip].index_char + 2;
		pi[ip].in = 1;
		tab = malloc(sizeof(int) * 2);
		tab[0] = pi[ip].index_char;
		tab[1] = ip;
		pi[ip].files[0] = strcpySpecial(p[ip], ' ', pi, tab);
		free(tab);
	}
}

void	infileSpaceDq(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 2;
	pi[ip].in = 1;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].files[0] = strcpySpecialDq(p[ip], pi, tab);
	pi[ip].index_char = pi[ip].index_char + 1;
	free(tab);
}

void	infileSpaceSq(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 2;
	pi[ip].in = 1;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].files[0] = strcpySpecialSq(p[ip], pi, tab);
	pi[ip].index_char = pi[ip].index_char + 1;
	free(tab);
}

void	infileFile(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 1;
	pi[ip].in = 1;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].files[0] = strcpySpecial(p[ip], ' ', pi, tab);
	free(tab);
}
