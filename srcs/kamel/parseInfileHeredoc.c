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

void	infileHeredoc(char **p, t_pipex *pi, int ip)
{
	while (p[ip][pi[ip].index_char + 2] == ' ')
		pi[ip].index_char = pi[ip].index_char + 1;
	if (p[ip][pi[ip].index_char + 2] == '"')
		heredocDq(p, pi, ip);
	else if (p[ip][pi[ip].index_char + 2] == '\'')
		heredocSq(p, pi, ip);
	else
		heredocFile(p, pi, ip);
}

void	heredocDq(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 3;
	pi[ip].here_doc = 1;
	pi[ip].in = 1;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].delimiteur = strcpySpecialDq(p[ip], pi, tab);
	// printf("\n\n%s\n\n", pi[ip].delimiteur);
	pi[ip].index_char = pi[ip].index_char + 1;
	pi[ip].files[0] = createHeredocFiles(ip);
	free(tab);
}

void	heredocSq(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 3;
	pi[ip].here_doc = 1;
	pi[ip].in = 1;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].delimiteur = strcpySpecialSq(p[ip], pi, tab);
	pi[ip].index_char = pi[ip].index_char + 1;
	pi[ip].files[0] = createHeredocFiles(ip);
	free(tab);
}

void	heredocFile(char **p, t_pipex *pi, int ip)
{
	int		*tab;

	pi[ip].index_char = pi[ip].index_char + 2;
	pi[ip].here_doc = 1;
	pi[ip].in = 1;
	tab = malloc(sizeof(int) * 2);
	tab[0] = pi[ip].index_char;
	tab[1] = ip;
	pi[ip].delimiteur = strcpySpecial(p[ip], ' ', pi, tab);
	pi[ip].files[0] = createHeredocFiles(ip);
	free(tab);
}
