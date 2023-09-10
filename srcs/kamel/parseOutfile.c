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

void	outfile(char **p, t_pipex *pi, int ip)
{
	if (checkOutfile(p[ip], pi[ip].index_char, pi, ip) == 0)
	{
		pi[ip].erreur = 1;
		return ;
	}
	if (p[ip][pi[ip].index_char + 1] == '>')
	{
		if (checkFileAppend(p[ip], pi[ip].index_char + 1, pi, ip) == 0)
		{
			pi[ip].erreur = 1;
			return ;
		}
		outfileAppend(p, pi, ip);
	}
	else if (p[ip][pi[ip].index_char + 1] == ' ')
		outfileSpaceFile(p, pi, ip);
	else if (p[ip][pi[ip].index_char + 1] == '"')
		outfileSpaceDq(p, pi, ip);
	else if (p[ip][pi[ip].index_char + 1] == '\'')
		outfileSpaceSq(p, pi, ip);
	else
		outfileFile(p, pi, ip);
}

void	outfileSpaceFile(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	while (p[ip][pi[ip].index_char + 2] == ' ')
		pi[ip].index_char = pi[ip].index_char + 1;
	if (p[ip][pi[ip].index_char + 2] == '"')
	{
		pi[ip].index_char = pi[ip].index_char + 3;
		tab = malloc(sizeof(int) * 2);
		tab[0] = pi[ip].index_char;
		tab[1] = ip;
		pi[ip].files[1] = strcpySpecialDq(p[ip], pi, tab);
	}
	else
	{
		pi[ip].index_char = pi[ip].index_char + 2;
		tab = malloc(sizeof(int) * 2);
		tab[0] = pi[ip].index_char;
		tab[1] = ip;
		pi[ip].files[1] = strcpySpecial(p[ip], ' ', pi, tab);
	}
}

void	outfileSpaceDq(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 2;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].files[1] = strcpySpecialDq(p[ip], pi, tab);
}

void	outfileSpaceSq(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 2;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].files[1] = strcpySpecialSq(p[ip], pi, tab);
}

void	outfileFile(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 1;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].files[1] = strcpySpecial(p[ip], ' ', pi, tab);
}
