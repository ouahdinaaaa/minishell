/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/20 13:48:43 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipex	*init_pipex(int parts, char **env)
{
	int		i;
	t_pipex	*pipex;

	i = 0;
	pipex = malloc(sizeof(t_pipex) * parts + 1);
	if (pipex == NULL)
		return (NULL);
	while (i < parts)
	{
		bzero_pipex(i, pipex);
		pipex[i].files[0] = NULL;
		pipex[i].files[1] = NULL;
		pipex[i].outfiles = NULL;
		pipex[i].infiles = NULL;
		pipex[i].cmd = NULL;
		pipex[i].delimiteur = NULL;
		pipex[i].env = ft_strcpy_double(env);
		pipex[i].path = NULL;
		pipex[i].size = parts;
		pipex[i].str_path = NULL;
		pipex[i].commande = NULL;
		i++;
	}
	return (pipex);
}

// void	ft_write_env(t_pipex *pipex, char **env)
// {
//	 pipex->env = ft_strcpy_double(env);
// 	return ;
// }

void	free_pipex_infiles_outfiles_env(t_pipex *pipex, int i)
{
	if (pipex[i].env)
		free_char_double(pipex[i].env);
	if (pipex[i].nbinfiles > 0)
		free_char_double(pipex[i].infiles);
	if (pipex[i].nboutfiles > 0)
		free_char_double(pipex[i].outfiles);
	if (pipex[i].commande)
		free(pipex[i].commande);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		if (pipex == NULL)
			return ;
		if (pipex[i].files[0])
			free(pipex[i].files[0]);
		if (pipex[i].files[1] != NULL)
			free(pipex[i].files[1]);
		if (pipex[i].cmd != NULL)
			free(pipex[i].cmd);
		if (pipex[i].delimiteur != NULL)
			free(pipex[i].delimiteur);
		if (pipex[i].path != NULL)
			free(pipex[i].path);
		if (pipex[i].str_path != NULL)
			free(pipex[i].str_path);
		if (pipex[i].fake_env)
			free_char_double(pipex[i].fake_env);
		free_pipex_infiles_outfiles_env(pipex, i);
		i++;
	}
	free(pipex);
}

void	bzero_pipex(int i, t_pipex *pipex)
{
	pipex[i].in = 0;
	pipex[i].out = 0;
	pipex[i].append = 0;
	pipex[i].size = 0;
	pipex[i].here_doc = 0;
	pipex[i].export_cmd = 0;
	pipex[i].pwd = 0;
	pipex[i].cd = 0;
	pipex[i].exit = 0;
	pipex[i].echo = 0;
	pipex[i].echo_n = 0;
	pipex[i].envi = 0;
	pipex[i].unset = 0;
	pipex[i].index_char = 0;
	pipex[i].erreur = 0;
	pipex[i].sq = 0;
	pipex[i].dq = 0;
	pipex[i].aya = 0;
	pipex[i].indexmot = 0;
	pipex[i].nbinfiles = 0;
	pipex[i].nboutfiles = 0;
}
