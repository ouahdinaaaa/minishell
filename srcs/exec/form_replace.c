/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 08:42:32 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/11 08:42:32 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*add_dollar(char *str)
{
	int		i;
	char	*str2;

	str2 = malloc(sizeof(char) * (ft_strlen(str) + 3));
	i = 0;
	str2[0] = '$';
	while (str[i])
	{
		str2[i + 1] = str[i];
		i++;
	}
	str2[i + 1] = '\0';
	return (str2);
}

void	replace_every_struct(t_pipex *pipex, int status)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		replace_files(&pipex[i], status);
		replace_out(&pipex[i], status);
		replace_str_path(&pipex[i], status);
		replace_path(&pipex[i], status);
		replace_str_cmd(&pipex[i], status);
		i++;
	}
}

void	replace_files(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str[2];
	int			i;

	i = 0;
	str[0] = NULL;
	if (pipex->files[0] && detect_dollar(pipex->files[0]))
	{
		new_str = ft_split(pipex->files[0], '$');
		if (detect_dollar(pipex->files[0]) == 2)
		{
			str[0] = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			i = 1;
			str[0] = ft_strcpy(str[0], new_str[0]);
		}
		while (new_str[i])
		{
			str[1] = replace_all(pipex, new_str[i], status);
			str[0] = ft_strjoin_gnl(str[0], str[1]);
			free(str[1]);
			i++;
		}
		end_function_files_in(new_str, pipex, str[0]);
	}
}

void	replace_out(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str[2];
	int			i;

	i = 0;
	str[0] = NULL;
	if (pipex->files[1] && detect_dollar(pipex->files[1]))
	{
		new_str = ft_split(pipex->files[1], '$');
		if (detect_dollar(pipex->files[1]) == 2)
		{
			i = 1;
			str[0] = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str[0] = ft_strcpy(str[0], new_str[0]);
		}
		while (new_str[i])
		{
			str[1] = replace_all(pipex, new_str[i], status);
			str[0] = ft_strjoin_gnl(str[0], str[1]);
			free(str[1]);
			i++;
		}
		end_function_files_out(new_str, pipex, str[0]);
	}
}

void	replace_str_path(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str[2];
	int			i;

	i = 0;
	str[0] = NULL;
	if (pipex->str_path && detect_dollar(pipex->str_path))
	{
		new_str = ft_split(pipex->str_path, '$');
		if (detect_dollar(pipex->str_path) == 2)
		{
			i = 1;
			str[0] = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str[0] = ft_strcpy(str[0], new_str[0]);
		}
		while (new_str[i])
		{
			str[1] = replace_all(pipex, new_str[i], status);
			str[0] = ft_strjoin_gnl(str[0], str[1]);
			free(str[1]);
			i++;
		}
		end_function_str_path(new_str, pipex, str[0]);
	}
}

char	*replace_echo(t_pipex *pipex, int status, char *new)
{
	char		**new_str;
	char		*str[2];
	int			i;

	i = 0;
	str[0] = NULL;
	if (new && detect_dollar(new))
	{
		new_str = ft_split(new, '$');
		if (detect_dollar(new) == 2)
		{
			i = 1;
			str[0] = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str[0] = ft_strcpy(str[0], new_str[0]);
		}
		while (new_str[i])
		{
			str[1] = replace_all(pipex, new_str[i], status);
			str[0] = ft_strjoin_gnl(str[0], str[1]);
			free(str[1]);
			i++;
		}
		return(free(new), free_char_double(new_str), str[0]);
	}
	return (new);
}
