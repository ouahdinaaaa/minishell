/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:26:42 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/20 14:50:36 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	verif_path(char *str, char **env, char **option)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoin("/", option[0]);
	if (!tmp2)
		return ;
	tmp = ft_strjoin(str, tmp2);
	if (!tmp)
	{
		free(tmp2);
		return ;
	}
	if (access(tmp, X_OK) == 0)
	{
		option[0] = tmp;
		create_nino(env, option);
	}
	free(tmp2);
	free(tmp);
	return ;
}

void	free_everythink(char **option, char *dest, t_cmd data, char **str)
{
	free_data(str);
	free(data.pids);
	free_data(option);
	free(dest);
}

void	create_path(t_pipex *pipex, t_cmd data, char *pwd, char **option)
{
	char	**str;
	char	*dest;
	int		i;
	int		o;

	i = 0;
	str = NULL;
	while (pipex->env[i])
	{
		if (!ft_strncmp("PATH", pipex->env[i], 4))
		{
			// env[i] += 5;
			str = ft_split(pipex->env[i] + 5, ':');
			o = 0;
			while (str[o])
				verif_path(str[o++], pipex->env, option);
		}
		i++;
	}
	dest = add_write_str("🤡 \033[34m [", option[0],
			"] \033[31m: Command not found 🤡\n", "");
	write(STDERR_FILENO, dest, ft_strlen(dest));
	free_everythink(option, dest, data, str);
	if (pipex->files[1] && pipex->here_doc)
		unlink(pipex->files[1]);
	free_pipex(pipex);
	free(pwd);
	exit(127);
}

void	create_nino(char **env, char **option)
{
	execve(option[0], option, env);
}
