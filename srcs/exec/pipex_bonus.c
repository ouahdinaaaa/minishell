/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:41:28 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/09 15:31:18 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	initdata(t_cmd *data, int nbcmd)
{
	data->i = 0;
	data->file = -1;
	data->infile = 0;
	data->here_doc = 0;
	data->prev_pipe = -1;
	data->res = NULL;
	data->ret = 0;
	data->nbcmd = nbcmd;
	data->pids = malloc(sizeof(int) * nbcmd);
	if (!data->pids)
		return ;
}

int	pipex_main(char **env, t_pipex *pipex, int status)
{
	t_cmd	data;

	if (!env || !*env || error_syntaxe(pipex))
		return (pipex[0].erreur);
	initdata(&data, pipex->size);
	if (!data.pids)
		return (free_dataa(&data), 1);
	replace_every_struct(pipex, status);
	status = second_pipex(data, pipex, env, status);
	return (status);
}

int	second_pipex(t_cmd data, t_pipex *pipex, char **env, int sta)
{
	int	status;

	data.i = 0;
	status = 0;
	int j = 0;
	pipex[0].erreur = -1;
	while (data.i < pipex[0].size)
	{
		if (pipex[0].size == 1 && (pipex[0].export_cmd
				|| pipex[0].unset || pipex[0].cd || pipex[0].exit))
			return (free(data.pids), choice_of_builtins(pipex, data.i));
		pipe(data.fd);
		data.pids[data.i] = fork();
		if (data.pids[data.i] == 0 && data.i == 0)
		{
			while (j < pipex[0].size)
			{
				// create_every_files(pipex[i].start_fd);
				if (pipex[j].here_doc)
				create_here_doc(pipex[j].files[0], pipex[j].delimiteur, pipex, sta);
				waitpid(data.pids[data.i], &status, 0);
				status = WEXITSTATUS(status);
				// dprintf(2, "erreur pipex : [%d]\n", pipex[0].erreur);
				if (status == 130)
					return (unlink(pipex[data.i].files[0]), close(pipex[0].erreur), status);
				j++;
			}
		}
		if (data.pids[data.i] == 0)
			child_process(data, env, pipex);
		else
		{
			close(data.fd[1]);
			if (data.prev_pipe != -1)
				close(data.prev_pipe);
			data.prev_pipe = data.fd[0];
		}
		data.i++;
	}
	status = end_function(data, pipex);
	return (close(data.fd[0]), status);
}
