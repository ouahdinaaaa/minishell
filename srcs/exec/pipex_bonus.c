/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:41:28 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/20 18:12:33 by ayael-ou         ###   ########.fr       */
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

int	pipex_main(char **env, t_pipex *pipex, int status, char *pwd)
{
	t_cmd	data;

	if (!env || !*env || error_syntaxe(pipex))
		return (pipex[0].erreur);
	initdata(&data, pipex->size);
	pipex[0].erreur = -1;
	if (!data.pids)
		return (free_dataa(&data), 1);
	replace_every_struct(pipex, status);
	status = second_pipex(data, pipex, status, pwd);
	return (status);
}

void	create_here_child(t_pipex *pipex, int sta, t_cmd data, char *pwd)
{
	int	*tab;

	tab = malloc(sizeof(int) * 3);
	tab[0] = sta;
	tab[1] = 0;
	tab[2] = 0;
	while (tab[1] < pipex[0].size)
	{
		if (pipex[tab[1]].here_doc)
		{
			create_here_doc(pipex, &data, tab, pwd);
			//waitpid(data.pids[data.i], &sta, 0);
			//sta = WEXITSTATUS(sta);
			//if (sta == 130)
			//{
			//	dprintf(2, "okkk in you\n");
			//	unlink(pipex[data.i].files[0]);
			//	close(pipex[0].erreur);
			//	exit(sta);
			//}
		}
		tab[1] += 1;
	}
	if (ctrl_c_signo != 125)
		free(tab);
}

int	second_pipex(t_cmd data, t_pipex *pipex, int sta, char *pwd)
{
	data.i = 0;
	while (data.i < pipex[0].size)
	{
		if (pipex[0].size == 1 && (pipex[0].export_cmd
				|| pipex[0].unset || pipex[0].cd || pipex[0].exit))
			return (free(data.pids), choice_of_builtins(pipex, 0, sta));
		pipe(data.fd);
		data.pids[data.i] = fork();
		if (data.pids[data.i] == 0 && data.i == 0)
			create_here_child(pipex, sta, data, pwd);
		if (data.pids[data.i] == 0)
			child_process(data, pipex, sta, pwd);
		else
		{
			close(data.fd[1]);
			if (data.prev_pipe != -1)
				close(data.prev_pipe);
			data.prev_pipe = data.fd[0];
		}
		data.i++;
	}
	sta = end_function(data, pipex);
	return (close(data.fd[0]), sta);
}
