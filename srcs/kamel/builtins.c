/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 18:21:57 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	checkBuiltins(t_pipex *pipex, int ip, char **motscmd)
{
	int	*tab;

	tab = malloc(sizeof(int) * 2);
	tab[0] = 0;
	tab[1] = ip;
	if (ft_strncp(motscmd[0], "export") == 0)
		checkExport(pipex, ip, motscmd);
	else if (ft_strncp(motscmd[0], "pwd") == 0)
		checkPwd(pipex, ip, motscmd);
	else if (ft_strncp(motscmd[0], "echo") == 0)
		checkEcho(pipex, ip, motscmd);
	else if (ft_strncp(motscmd[0], "cd") == 0)
		checkCd(pipex, ip, motscmd);
	else if (ft_strncp(motscmd[0], "exit") == 0)
		check_exit(pipex, ip, motscmd);
	else if (ft_strncp(motscmd[0], "unset") == 0)
		checkUnset(pipex, ip, motscmd);
	else if (ft_strncp(motscmd[0], "env") == 0)
		checkEnv(pipex, ip);
	free(tab);
}

void	checkCd(t_pipex *pipex, int ip, char **cmd)
{
	pipex[ip].cd = 1;
	if (cmd[1])
		pipex[ip].path = ft_strdup(cmd[1]);
	if (ft_countwords(pipex[ip].cmd) > 2)
		pipex[ip].cd = 2;
}

void	checkEcho(t_pipex *pipex, int ip, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[i + 1] && ft_strncp(cmd[i + 1], "-n") == 0)
	{
		i = i + 2;
		pipex[ip].echo_n = 1;
		while (cmd[i] != NULL)
			pipex[ip].str_path = concatwithspace(pipex[ip].str_path, cmd[i++]);
	}
	else
	{
		i = 1;
		pipex[ip].echo = 1;
		while (cmd[i] != NULL)
			pipex[ip].str_path = concatwithspace(pipex[ip].str_path, cmd[i++]);
	}
}

void	checkEnv(t_pipex *pipex, int ip)
{
	pipex[ip].envi = 1;
}

void	check_exit(t_pipex *pipex, int ip, char **cmd)
{
	(void)cmd;
	if (ft_countwords(pipex[ip].cmd) > 2)
		pipex[ip].exit = 2;
	else
		pipex[ip].exit = 1;
}
