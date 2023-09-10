/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:11:21 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 19:11:21 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	find_end_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**malloc_of_str(char **str, int len_str, t_pipex builtins, int place)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (builtins.env[i])
	{
		if (i == place)
			i++;
		else
		{
			len = ft_strlen(builtins.env[i]) + 1;
			str[i] = ft_calloc(sizeof(char), (len + 1));
			str[i] = ft_strcpy(str[i], builtins.env[i]);
			i++;
		}
	}
	len = i;
	if (place != -1)
		i = place;
	str[i] = ft_calloc(sizeof(char), (len_str + 1));
	str[i] = ft_strcpy(str[i], builtins.str_path);
	str[len + 1] = NULL;
	return (str);
}

int	find_env(char **env, char *str_path, int place)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str_path, (place + 1)))
			return (i);
		i++;
	}
	return (-1);
}


void	add_path(char *add_path, t_pipex *builtins, int place)
{
	// int		len;
	int		len_str;
	char	**new_str;
	int		find_path;
	char	*dest;

	find_path = find_end_path(builtins[place].str_path);
	// len = size_of_env(builtins[place].env);
	len_str = ft_strlen(add_path);
	if (find_path == -1)
		return ;
	if (builtins->str_path[0] == '=')
	{
		dest = add_write_str("\033[34mexport : '", builtins[place].str_path, "' \033[31m: not a valid identifier\n" , "");
	 	write(STDERR_FILENO, dest, ft_strlen(dest));
		free(dest);
		return ;
	}
	else
	{
		find_path = find_env(builtins[place].env, 
				builtins[place].str_path, find_path);
		new_str = malloc(sizeof(char *) * (size_of_env(builtins[place].env) + 2));
		new_str = malloc_of_str(new_str, len_str, builtins[place], find_path);
		edit_env(new_str, builtins);
	}
}

int	cmd_export(t_pipex *builtins, t_pipex *pipex, int i)
{
	char	**str_to_add;
	int		j;

	j = 0;
	if (!pipex[i].str_path)
		return (print_env(pipex[0].fake_env), 1);
	str_to_add = ft_split_pip(builtins->str_path, ' ');
	while (str_to_add[j])
	{
		free(builtins->str_path);
		builtins->str_path = str_to_add[j];
		add_path(builtins->str_path, pipex, i);
		j++;
	}
	free(str_to_add);
	return (1);
}
