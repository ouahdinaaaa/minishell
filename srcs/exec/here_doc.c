/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:58:18 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/10 04:23:57 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	free_dataa(t_cmd *data)
{
	if (data->pids)
		free(data->pids);
	if (data)
		free(data);
}


int	ft_strncmp_here(char *s1, char *s2, size_t n, int nb)
{
	size_t	i;

	i = 0;
	if ((n <= 0 || (ft_strlen(s1) != (ft_strlen(s2) - 1))) && nb)
		return (1);
	if (!nb)
	{
		if (ft_strlen(s1) != ft_strlen(s2) ||
			(!s2 && ft_strlen(s1) != ft_strlen(s2)))
			return (1);
		while ((s1[i] && s2[i]) && s1[i] == s2[i])
			i++;
		return (s1[i] - s2[i]);
	}
	i = 0;
	while (s1[i] == s2[i] && i < n - 1 && nb)
		i++;
	return (s1[i] - s2[i]);
}

void	ft_ctrl_here(char *limiteur)
{
	char *dest;

	dest = add_write_str("minishell : warning : here_document at line by end_of_file (wanted '", limiteur, "')\n", "");
	write(STDERR_FILENO, dest, ft_strlen(dest));
	free(dest);
}


void	signal_ctrl_c_here(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(130);
	close(0);
}

int verif_delimiteur(char *str)
{
	if (str[0] == '"' && str[ft_strlen(str)] == '"')
		return (0);
	return(1);
}

char	*replace_limiteur(char *str)
{
	char *str2;
	int	i;
	int j;

	i = 0;
	j = 1;
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[j] && j < (int)ft_strlen(str))
	{
		str2[i] = str[j];
		i++;
		j++;
	}
	str2[i] = '\0';
	free(str);
	return(str2);
}

void	create_here_doc(char *infile, char *limiter, t_pipex *pipex, int sta)
{
	char	*str = NULL;
	int		file_here;
	int		replace = 0;
	
	replace = verif_delimiteur(limiter);
	if (!replace)
		limiter = replace_limiteur(limiter);
	file_here = open(infile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	pipex[0].erreur = file_here;
	if (file_here < 0)
	{
		unlink(infile);
		ft_putendl_fd("failded fd here_doc\n", 2);
	}
	while (1)
	{
		signal(SIGINT, signal_ctrl_c_here);
		str = readline(ORANGE"✍️ > ");
		if (str == NULL)
		{
			ft_ctrl_here(limiter);
			break ;
		}
		if (!ft_strncmp_here(limiter, str, (ft_strlen(limiter)), 0))
			break ;
		if (replace)
			str = replace_str_here(str, sta, pipex);
		ft_putstr_fd(str, file_here);
		ft_putstr_fd("\n", file_here);
		free(str);
	}
	free(str);
	close(file_here);
}

void	delete_here_doc(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		if (pipex[i].here_doc)
			unlink(pipex[i].files[0]);
		i++;
	}
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
