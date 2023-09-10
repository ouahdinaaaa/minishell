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

void	checkEcho(t_pipex *pipex, int ip)
{
	char	*opt;

	opt = strcpyOption(pipex, ip);
	if (ft_strncp(opt, "-n") == 0)
	{
		pipex[ip].echo_n = 1;
		strcpyEchoN(pipex, ip);
	}
	else
	{
		pipex[ip].echo = 1;
		pipex[ip].str_path = strcpyEcho(pipex, ip);
	}
	free(opt);
}

char	*strcpyOption(t_pipex *pipex, int index_pipe)
{
	int	i;
	int	*tab;
	char *str;

	tab = malloc(sizeof(int) * 2);
	i = 0;
	while (pipex[index_pipe].cmd[i] && pipex[index_pipe].cmd[i] != ' ')
		i++;
	while (pipex[index_pipe].cmd[i] && pipex[index_pipe].cmd[i] == ' ')
		i++;
	tab[0] = i;
	tab[1] = index_pipe;
	str = strcpySpecial(pipex[index_pipe].cmd, ' ', pipex, tab);
	free(tab);
	return (str);
}

void	strcpyEchoN(t_pipex *pipex, int ip)
{
	int	i;
	int	*tab;

	i = 0;
	while (pipex[ip].cmd[i] && pipex[ip].cmd[i] != ' ')
		i++;
	while (pipex[ip].cmd[i] && pipex[ip].cmd[i] == ' ')
		i++;
	while (pipex[ip].cmd[i] && pipex[ip].cmd[i] != ' ')
		i++;
	while (pipex[ip].cmd[i] && pipex[ip].cmd[i] == ' ')
		i++;
	tab = malloc(sizeof(int) * 2);
	tab[0] = i;
	tab[1] = ip;
	pipex[ip].str_path = strcpySpecial(pipex[ip].cmd, '>', pipex, tab);
	free(tab);
}

char	*strcpyEcho(t_pipex *pipex, int index_pipe)
{
	int	i;
	int	*tab;
	char *str;

	tab = malloc(sizeof(int) * 2);
	i = 0;
	while (pipex[index_pipe].cmd[i] && pipex[index_pipe].cmd[i] != ' ')
		i++;
	while (pipex[index_pipe].cmd[i] && pipex[index_pipe].cmd[i] == ' ')
		i++;
	tab[0] = i;
	tab[1] = index_pipe;
	str = strcpySpecial(pipex[index_pipe].cmd, '>', pipex, tab);
	free(tab);
	return (str);
}
