/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 19:27:52 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing(char *commande, t_pipex *pi, char **env)
{
	char	**p;		// Les pipes
	int		ip;			// Index pipe
	int		nb_p;		// Nombre de pipes
	char **words;		// Tableau de mots
    char     **cmd;
    int indexcmd;
    int j;
    int in;
    int out;
	(void)env;

	nb_p = ft_count_pipes(commande);
	p = splitPipes(commande);
	ip = 0;
    in = 0;
    out = 0;
	while (ip <= nb_p)
	{
        indexcmd = 0;
        if (ft_count_files('<', p[ip]) > 0)
            pi[ip].infiles = malloc(sizeof(char *) * (ft_count_files('<', p[ip]) + 1));
        if (ft_count_files('>', p[ip]) > 0)
            pi[ip].outfiles = malloc(sizeof(char *) * (ft_count_files('>', p[ip]) + 1));
        if (conditionsquotesimpaires(p, ip))
			return (quotesimpaires(p, pi, ip));
		if (p[ip] == NULL || check_only_spaces(p[ip]))
		{
			break;
        	pi[ip].cmd = NULL;
		}
		words = decoupage(convertirDollarEnEuro(p[ip]));
        j = 0;
        while (j < ft_countwords(p[ip]))
        {
            if (!ft_strncp(words[j], "<<<") || !ft_strncp(words[j], ">>>"))
            {
                pi[0].erreur = 0;
                free_char_double(words);
                return ;
            }
            j++;
        }
        cmd = malloc(sizeof(char *) * (ft_countwords(p[ip]) + 1));
        j = 0;
        while (j < ft_countwords(p[ip]))
        {
            if (isstartingwith(words[j], "<<") && ft_strlen(words[j]) == 2)
            {
                pi[ip].in = 1;
                if (pi[ip].here_doc >= 1)
                    pi[ip].here_doc = 2;
                else
                {
                    pi[ip].here_doc = 1;
                    if (pi[ip].files[0])
			            free(pi[ip].files[0]);
                    pi[ip].files[0] = createHeredocFiles(ip);
                }
                if (words[j + 1])
                    pi[ip].delimiteur = ft_strdup(words[j + 1]);
                j++;
            }
            else if (isstartingwith(words[j], "<<") && ft_strlen(words[j]) > 2)
            {
                pi[ip].in = 1;
                if (pi[ip].here_doc >= 1)
                    pi[ip].here_doc = 2;
                else
                {
                    pi[ip].here_doc = 1;
                    if (pi[ip].files[0] != NULL)
                        free(pi[ip].files[0]);
                    pi[ip].files[0] = createHeredocFiles(ip);
                }
                pi[ip].delimiteur = ft_strdup(words[j] + 2);
            }
            else if (isstartingwith(words[j], "<") && ft_strlen(words[j]) == 1)
            {
                pi[ip].in = 1;
                if (words[j + 1])
                {
                    pi[ip].files[0] = ft_strdup(words[j + 1]);
                    pi[ip].infiles[in++] = ft_strdup(words[j + 1]);
                }
                else
                {
                    pi[0].erreur = 2;
                    printf("Minishell : syntax error near unexpected token `newline'\n");
                }
                j++;
            }
            else if (isstartingwith(words[j], "<") && ft_strlen(words[j]) > 1)
            {
                pi[ip].in = 1;
                pi[ip].files[0] = ft_strdup(words[j] + 1);
                pi[ip].infiles[in++] = ft_strdup(words[j] + 1);
            }
            else if (isstartingwith(words[j], ">>") && ft_strlen(words[j]) == 2)
            {
                pi[ip].out = 1;
                pi[ip].append = 1;
                if (words[j + 1])
                    pi[ip].files[1] = ft_strdup(words[j + 1]);
                j++;
            }
            else if (isstartingwith(words[j], ">>") && ft_strlen(words[j]) > 2)
            {
                pi[ip].out = 1;
                pi[ip].append = 1;
                pi[ip].files[1] = ft_strdup(words[j] + 2);
            }
            else if (isstartingwith(words[j], ">") && ft_strlen(words[j]) == 1)
            {
                pi[ip].out = 1;
                if (words[j + 1])
                {
                    pi[ip].files[1] = ft_strdup(words[j + 1]);
                    pi[ip].outfiles[out++] = ft_strdup(words[j + 1]);
                }
                else
                {
                    pi[0].erreur = 2;
                    printf("Minishell : syntax error near unexpected token `newline'\n");
                }
                j++;
            }
            else if (isstartingwith(words[j], ">") && ft_strlen(words[j]) > 1)
            {
                pi[ip].out = 1;
                pi[ip].files[1] = ft_strdup(words[j] + 1);
                pi[ip].outfiles[out++] = ft_strdup(words[j] + 1);
            }
            else
            {
                pi[ip].cmd = concatwithspace(pi[ip].cmd, words[j]);
                cmd[indexcmd++] = ft_strdup(words[j]);
            }
            j++;
        }
        cmd[indexcmd] = NULL;
        if (ft_count_files('<', p[ip]) > 0)
            pi[ip].infiles[in] = NULL;
        if (ft_count_files('>', p[ip]) > 0)
            pi[ip].outfiles[out] = NULL;
        if (pi[ip].cmd && pi[ip].cmd != NULL)
            checkBuiltins(pi, ip, cmd);
        ip++;
        free_char_double(cmd);
        free_char_double(words);
    }
    free_char_double(p);
}
