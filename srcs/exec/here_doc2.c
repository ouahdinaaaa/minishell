/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:46:09 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/11 09:46:09 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	verif_replace_here(char *str)
{
	if (str[0] != '"' && str[(ft_strlen(str) - 1)] != '"')
		return (1);
	return (0);
}

char	*replace_limiteur(char *str)
{
	char	*str2;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (str[0] != '"' && str[(ft_strlen(str) - 1)] != '"')
		return (str);
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[j] && j < (int)(ft_strlen(str) - 1))
	{
		str2[i] = str[j];
		i++;
		j++;
	}
	str2[i] = '\0';
	free(str);
	return (str2);
}

int	condition_of_break(char *str, char *limiter)
{
	int	nb;

	nb = 0;
	if (str == NULL)
	{
		ft_ctrl_here(limiter);
		nb = 1;
	}
	if (str == NULL)
		nb = 1;
	if (!ft_strncmp_here(limiter, str, (ft_strlen(limiter)), 0))
	{
		free(str);
		nb = 1;
	}
	return (nb);
}

void	create_here_doc(t_pipex *pipex, t_cmd *data, int *tab, char *pwd)
{
	char	*str;
	int		file_here;
	int		replace;

	replace = verif_replace_here(pipex[tab[1]].delimiteur);
	pipex[tab[1]].delimiteur = replace_limiteur(pipex[tab[1]].delimiteur);
	file_here = open(pipex[tab[1]].files[0], O_CREAT | O_TRUNC | O_WRONLY, 0666);
	//tab[2] = file_here;
	pipex[0].erreur = file_here;
	if (file_here < 0)
	{
		unlink(pipex[tab[1]].files[0]);
		write(STDERR_FILENO, "failded fd here_doc\n", 21);
	}
	while (1)
	{
		signal(SIGINT, signal_ctrl_c_here);
		if (ctrl_c_signo == 120)
		{
			free_pipex(pipex);
			free(data->pids);
			free(tab);
			free(pwd);
			close(file_here);
			exit(130);
		}
		str = readline(ORANGE"✍️ > ");
		if (condition_of_break(str, pipex[tab[1]].delimiteur))
			break ;
		if (replace)
			str = replace_str_here(str, tab[0], pipex);
		ft_putendl_fd(str, file_here);
		free(str);
	}
	close(file_here);
}

int	end_function(t_cmd data, t_pipex *pipex)
{
	int	status;

	data.i = 0;
	while (data.i < pipex[0].size)
	{
		waitpid(data.pids[data.i], &status, 0);
		status = WEXITSTATUS(status);
		data.i++;
	}
	delete_here_doc(pipex);
	free(data.pids);
	return (status);
}
