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

void	checkExport(t_pipex *pipex, int ip)
{
	pipex[ip].export_cmd = 1;
	pipex[ip].str_path = strcpyExport(pipex, ip);
}

char	*strcpyExport(t_pipex *pipex, int index_pipe)
{
	int	i;
	int	*tab;
	char *str;

	tab = malloc(sizeof(int) * 2);
	i = 0;
	while (pipex[index_pipe].cmd[i] && pipex[index_pipe].cmd[i] != ' ')
		i++;
	if (pipex[index_pipe].cmd[i] && pipex[index_pipe].cmd[i] == ' ')
		i++;
	tab[0] = i;
	tab[1] = index_pipe;
	str = strcpySpecial(pipex[index_pipe].cmd, '\0', pipex, tab);
	free(tab);
	return (str);
}
