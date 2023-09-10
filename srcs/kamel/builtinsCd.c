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

void	checkCd(t_pipex *pipex, int ip)
{
	pipex[ip].cd = 1;
	pipex[ip].path = strcpyCd(pipex, ip);
	if (countWordsCd(pipex[ip].cmd) > 2)
		pipex[ip].cd = 2;
}

char	*strcpyCd(t_pipex *pipex, int index_pipe)
{
	int	i;
	int	*tab;
	char *str;

	tab = malloc(sizeof(int) * 2);
	i = 0;
	while (pipex[index_pipe].cmd[i] && pipex[index_pipe].cmd[i] != ' ')
		i++;
	i++;
	tab[0] = i;
	tab[1] = index_pipe;
	str = strcpySpecial(pipex[index_pipe].cmd, ' ', pipex, tab);
	free(tab);
	return (str);
}
