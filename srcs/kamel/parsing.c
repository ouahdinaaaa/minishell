/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/24 21:48:00 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *commande, t_pipex *pi, char **env)
{
	char	**p;		// Les pipes
	int		ip;			// Index pipe
	int		nb_p;		// Nombre de pipes
	char **words;		// Tableau de mots
	(void)env;

	nb_p = countPipes(commande);
	p = splitPipes(commande);
	ip = 0;
	while (ip <= nb_p)
	{
		if (p[ip] == NULL || onlySpaces(p[ip]))
		{
			break;
        	pi[ip].cmd = NULL;
		}
		words = quotes(convertirDollarEnEuro(p[ip]));
    	p[ip] = collerMots(words, countWords(p[ip]));
		if (isEven(countSingleQuotes(p[ip])) == 0
			|| isEven(countDoubleQuotes(p[ip])) == 0
			|| countParentheses(p[ip]) != 0)
		{
			printf("\nError : Nombre de quotes ou parentheses impair");
			free_double(p);
			return ;
		}
		pi[ip].index_char = 0;
		pi[ip].index_char = skipFirstSpaces(p[ip]);
		if (p[ip][pi[ip].index_char] == '<')
			infile(p, pi, ip);
		while (p[ip][pi[ip].index_char] == ' ')
			pi[ip].index_char = pi[ip].index_char + 1;
		stockage_commande(p, pi, ip);
		while (p[ip][pi[ip].index_char] == ' ')
			pi[ip].index_char = pi[ip].index_char + 1;
		// if (containsdollarsign(pi[ip].cmd) == 1)
		// 	pi[ip].cmd = extractsubstring(pi[ip].cmd);
		cmdopt(pi, ip, pi[ip].cmd, p);
		pi[ip].cmd = clear_cmd(pi[ip].cmd);
		checkBuiltins(pi, ip);
		spaceManagement(pi, ip);
		ip++;
	}
	free_double(p);
}
