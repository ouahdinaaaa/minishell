/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:12:05 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 19:12:05 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	**restruct(char **str, int place)
{
	char	**new_str;
	int	j;
	int	i;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char *) * (size_of_env(str) + 1));
	while (str[i])
	{
		if (place == i)
			i++;
		else 
		{
			new_str[j] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
			new_str[j] = ft_strcpy(new_str[j], str[i]);
			i++;
			j++;
		}
	}
	new_str[j] = NULL;
	return (new_str);
}

void	delete_unset(char **env, char *path, t_pipex *pipex)
{
	char	**envi;
	int	i;
	char	**tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], path, (ft_strlen(path)))
			&& env[i][ft_strlen(path)] == '=')
			break ;
		i++;
	}
	tmp = restruct(env, i);
	envi = ft_strcpy_double(tmp);
	free_char_double(tmp);
	edit_env(envi, pipex);
}

void	edit_env(char **str, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		if (pipex[i].env)
		{
			free_char_double(pipex[i].env);
			pipex[i].env = str;
		}
		i++;
	}
}

int	cmd_unset(t_pipex *builtins, t_pipex *pipex)
{
	char	**unset_path;
	int		i;

	i = 0;
	if (!builtins->str_path)
		return(1);
	unset_path = ft_split(builtins->str_path, ' ');
	while (unset_path[i])
	{
		free(builtins->str_path);
		builtins->str_path = unset_path[i];
		delete_unset(builtins->env, builtins->str_path, pipex);
		i++;
	}
	free(unset_path);
	return (1);
}
