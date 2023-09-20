/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:34:40 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	checkExport(t_pipex *pipex, int ip, char **cmd)
{
	int	i;

	i = 1;
	pipex[ip].export_cmd = 1;
	while (cmd[i] != NULL)
		pipex[ip].str_path = concatwithspace(pipex[ip].str_path, cmd[i++]);
}

void	checkPwd(t_pipex *pipex, int ip, char **cmd)
{
	(void)cmd;
	pipex[ip].pwd = 1;
}

void	checkUnset(t_pipex *pipex, int ip, char **cmd)
{
	int	i;

	i = 1;
	(void)cmd;
	pipex[ip].unset = 1;
	while (cmd[i] != NULL)
		pipex[ip].str_path = concatwithspace(pipex[ip].str_path, cmd[i++]);
}
