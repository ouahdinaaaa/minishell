/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:15:32 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/10 03:41:57 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	free_data(char **option)
{
	int	i;

	i = 0;
	if (!option)
		return ;
	while (option[i])
	{
		free(option[i]);
		i++;
	}
	free(option);
}

void	exec_cmd(t_pipex *pipex, t_cmd data, char **env, int boolean)
{
	char	**option;
	char	*dest;

	if (boolean)
	{
		option = split_cmd(pipex->cmd);
		if (execve(option[0], option, env) == -1)
		{
			dest =  add_write_str(" 🙅‍♀️  \033[34m [", option[0], "] \033[31m: No such file or directory\033[1;97m 🙅‍♀️\n", "");
	 		write(STDERR_FILENO, dest, ft_strlen(dest));
			free(dest);
			free_data(option);
			free(data.pids);
			if (pipex->files[1] && pipex->here_doc)
				unlink(pipex->files[1]);
		}
		exit(127);
	}
	else
	{
		option = split_cmd(pipex->cmd);
		create_path(pipex, data, env, option);
	}
}
