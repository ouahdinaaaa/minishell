/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_fake_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:41:55 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/18 04:41:55 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	edit_fake_env(char **str, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		if (pipex[i].fake_env)
		{
			free_char_double(pipex[i].fake_env);
			pipex[i].fake_env = ft_strcpy_double(str);
		}
		i++;
	}
}

char	**write_of_str_export(char **str, t_pipex builtins, int place)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (builtins.env[i])
	{
		len = ft_strlen(builtins.env[i]) + 1;
		str[i] = ft_calloc(sizeof(char), (len + 1));
		str[i] = ft_strcpy(str[i], builtins.env[i]);
		i++;
	}
	len = i;
	if (place != -1)
	{
		i = place;
		free(str[i]);
		str[i] = ft_calloc(sizeof(char), (len_str + 1));
		str[i] = ft_strcpy(str[i], builtins.str_path);
	}
	else
	{
		str[i] = ft_calloc(sizeof(char), (len_str + 1));
		str[i] = ft_strcpy(str[i], builtins.str_path);
		str[i + 1] = NULL;
	}
	if (i == len)
		len++;
	str[len] = NULL;
	return (str);
}

int	find_env_fake(char **env, char *str_path, int place)
{
	char	*join;
	int		i;

	i = 0;
	join = ft_strjoin("export ", str_path);
	while (env[i])
	{
		if (!ft_strncmp(env[i], join, (place + 8)))
		{
			free(join);
			return (i);
		}
		i++;
	}
	free(join);
	return (-1);
}

void	add_fake_env(char *str_path, t_pipex *pipex, int place)
{
	char	**new_env;
	int		find_path;
	int		len;

	(void)str_path;
	len = size_of_env(pipex[place].fake_env);
	new_env = malloc(sizeof(char *) * (len + 2));
	find_path = find_env_fake(pipex[place].fake_env,
			str_path, place);
	write_of_str_export(new_env, pipex[place], find_path);
	sort_new_env(&new_env, len, 24);
	edit_fake_env(new_env, pipex);
	free_char_double(new_env);
}
