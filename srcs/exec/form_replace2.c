/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_replace2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 08:39:44 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/11 08:39:44 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	replace_path(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str[2];
	int			i;

	i = 0;
	str[0] = NULL;
	if (pipex->path && detect_dollar(pipex->path))
	{
		new_str = ft_split(pipex->path, '$');
		if (detect_dollar(pipex->path) == 2)
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
		end_function_path(new_str, pipex, str[0]);
	}
}

void	replace_str_cmd(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str[2];
	int			i;

	i = 0;
	str[0] = NULL;
	if (pipex->cmd && detect_dollar(pipex->cmd))
	{
		new_str = ft_split(pipex->cmd, '$');
		if (detect_dollar(pipex->cmd) == 2)
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
		end_function_cmd(new_str, pipex, str[0]);
	}
}

char	*delete_char(char *src)
{
	char	*str;
	int		i;
	int		j;

	i = 1;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!str)
		return (NULL);
	while (src[i])
	{
		str[j] = src[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(src);
	return (str);
}

void	free_files(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}
