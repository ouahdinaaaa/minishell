/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:58:38 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/07/10 15:58:38 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_pipex(char *cmd, t_pipex *pipex)
{
	if (pipex->echo || pipex->unset || pipex->export_cmd)
		pipex->str_path = cmd;
	else if (pipex->cd)
		pipex->path = cmd;
}

int	verif_cmd(t_pipex pipex)
{
	int	value;

	value = 0;
	if (!pipex.export_cmd && !pipex.unset && !pipex.cd && !pipex.echo)
		value = 1;
	return (value);
}

void	free_all_sep(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i])
			free(env[i]);
		i++;
	}
	free(env);
}

char	**ft_strcpy_double(char **env_copy)
{
	char	**str;
	// int	size;
	int	i;

	// size = size_of_env(env_copy);
	i = 0;
	str = malloc(sizeof(char *) * (1000));
	while (env_copy[i])
	{
		str[i] = malloc(sizeof(char) * (ft_strlen(env_copy[i]) + 1));
		ft_strcpy(str[i], env_copy[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}