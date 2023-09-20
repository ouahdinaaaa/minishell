/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:15:22 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/07/09 16:15:22 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	choice_of_coloris(t_pipex *pipex, int index)
{
	if (pipex[index].pwd)
		printf(ROSE);
	else if (pipex[index].env)
		printf(BLEU_E);
	else if (pipex[index].echo)
		printf(BLANC);
	else
		return ;
}

void	verif_pipe(t_cmd *data, const int index, t_pipex *pipex)
{
	if (pipex[index].in)
		readfile(*data, pipex[index].files[0]);
	else if (!pipex[index].in)
		dup2(data->prev_pipe, STDIN_FILENO);
	if (!pipex[index].out && index != pipex[0].size -1)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (pipex[index].out)
		write_file(*data, pipex[index].files[1], pipex[index].append);
	else
		choice_of_coloris(pipex, index);
}

void	is_child(t_cmd *data, const int index, t_pipex *pipex)
{
	verif_pipe(data, index, pipex);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	child_process(t_cmd data, t_pipex *pipex, int status, char *pwd)
{
	char	**str;

	is_child(&data, data.i, pipex);
	if (choice_of_builtins(pipex, data.i, status))
	{
		free(data.pids);
		free_pipex(pipex);
		free(pwd);
		//if (data.i == (pipex[0].seize - 1))
			//close(data.prev_pipe);
		exit(0);
	}
	str = ft_split(pipex[data.i].cmd, ' ');
	if (ft_strchr(str[0], '/'))
	{
		free_char_double(str);
		exec_cmd(&pipex[data.i], data, pwd, 1);
	}
	else
	{
		free_char_double(str);
		exec_cmd(&pipex[data.i], data, pwd, 0);
	}
}
