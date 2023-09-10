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

void	checkBuiltins(t_pipex *pipex, int ip)
{
	char	*cmd;
	int		*tab;

	tab = malloc(sizeof(int) * 2);
	tab[0] = 0;
	tab[1] = ip;
	cmd = strcpySpecial(pipex[ip].cmd, ' ', pipex, tab);
	if (ft_strncp(cmd, "export") == 0 || ft_strncp(cmd, "\"export\"") == 0)
		checkExport(pipex, ip);
	else if (ft_strncp(cmd, "pwd") == 0 || ft_strncp(cmd, "\"pwd\"") == 0)
		checkPwd(pipex, ip);
	else if (ft_strncp(cmd, "echo") == 0 || ft_strncp(cmd, "\"echo\"") == 0)
		checkEcho(pipex, ip);
	else if (ft_strncp(cmd, "cd") == 0 || ft_strncp(cmd, "\"cd\"") == 0)
		checkCd(pipex, ip);
	else if (ft_strncp(cmd, "exit") == 0 || ft_strncp(cmd, "\"exit\"") == 0)
		checkExit(pipex, ip);
	else if (ft_strncp(cmd, "unset") == 0 || ft_strncp(cmd, "\"unset\"") == 0)
		checkUnset(pipex, ip);
	else if (ft_strncp(cmd, "env") == 0 || ft_strncp(cmd, "\"env\"") == 0)
		checkEnv(pipex, ip);
	free(tab);
	free(cmd);
}

void	spaceManagement(t_pipex *pipex, int ip)
{
	if (onlySpaces(pipex[ip].str_path) == 1)
	{
		free(pipex[ip].str_path);
		pipex[ip].str_path = NULL;
	}
	if (onlySpaces(pipex[ip].path) == 1)
	{
		free(pipex[ip].path);
		pipex[ip].path = NULL;
	}
}

int	onlySpaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
