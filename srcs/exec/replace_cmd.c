/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:02:57 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/07/10 18:02:57 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	replace(t_pipex pipex)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while (pipex.cmd[i])
	{
		if (pipex.cmd[i] == '=')
			break ;
		i++;
	}
	end = i;
	pipex.cmd = ft_substr(pipex.cmd, 0, end);
	i = 0;
	while (pipex.env[i])
	{
		if (!ft_strncmp_pipex(pipex.cmd, pipex.env[i], end, 0))
		{
			pipex.cmd = pipex.env[i];
			return ;
		}
		i++;
	}
}

int	detect_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '$')
		return (1);
	while (str[i])
	{
		if (str[i] == '$')
			return (2);
		i++;
	}
	return (0);
}
