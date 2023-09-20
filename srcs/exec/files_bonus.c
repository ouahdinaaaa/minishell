/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:31:11 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/11 16:10:30 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	dup_and_close(int fd, int re)
{
	dup2(fd, re);
	close(fd);
}

char	**split_cmd(char *av)
{
	char	**option;

	option = ft_split_pip(av, ' ');
	return (option);
}

void	make_erreur(t_cmd data)
{
	close(data.fd[0]);
	close(data.fd[1]);
	free(data.pids);
	exit(1);
}

void	readfile(t_cmd data, char *infile)
{
	char	*dest;
	int		file;

	file = open(infile, O_RDONLY);
	if (file < 0)
	{
		if (access(infile, F_OK) != 0)
		{
			dest = add_write_str("🙊  \033[38m : ", infile,
					"\033[36m: No such file or directory  🙊\n", "");
			write(STDERR_FILENO, dest, ft_strlen(dest));
			free(dest);
			make_erreur(data);
		}
		dest = add_write_str("⛔   \033[38m : ", infile,
				"\033[36m: No such file or directory  ⛔\n", "");
		write(STDERR_FILENO, dest, ft_strlen(dest));
		free(dest);
		make_erreur(data);
	}
	dup_and_close(file, STDIN_FILENO);
}

void	write_file(t_cmd data, char *outfile, int boolean)
{
	char	*dest;

	if (boolean)
		data.file = open(outfile, O_APPEND | O_CREAT | O_WRONLY, 0000644);
	else
		data.file = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (data.file < 0)
	{
		dest = add_write_str("⛔ \033[32m", outfile,
				": Permission denied\033[1;97m  ⛔\n", "");
		write(STDERR_FILENO, dest, ft_strlen(dest));
		free(dest);
		close(data.fd[0]);
		close(data.fd[1]);
		close(data.prev_pipe);
		free(data.pids);
		exit(1);
	}
	else
		dup_and_close(data.file, STDOUT_FILENO);
}
