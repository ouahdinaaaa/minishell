/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/09 22:11:01 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*init_pipex(int parts, char **env)
{
	int		i;
	t_pipex	*pipex;

	i = 0;
	pipex = malloc(sizeof(t_pipex) * parts);
	if (pipex == NULL)
		return (NULL);
	while (i < parts)
	{
		bzero_pipex(i, pipex);
		pipex[i].files[0] = NULL;
		pipex[i].files[1] = NULL;
		pipex[i].cmd = NULL;
		pipex[i].delimiteur = NULL;
		write_env(&pipex[i], env);
		pipex[i].path = NULL;
		pipex[i].size = parts;
		pipex[i].str_path = NULL;
		i++;
	}
	return (pipex);
}

void    write_env(t_pipex *pipex, char **env)
{
    pipex->env = ft_strcpy_double(env);
    return ;
}

void	free_pipex(t_pipex *pipex)
{
	int	i;
	i = 0;
	while (i < pipex[0].size)
	{
		if (pipex == NULL)
			return ;
		if (pipex[i].files[0])
			free(pipex[i].files[0]);
		if (pipex[i].files[1] != NULL)
			free(pipex[i].files[1]);
		if (pipex[i].cmd != NULL)
			free(pipex[i].cmd);
		if (pipex[i].delimiteur != NULL)
			free(pipex[i].delimiteur);
		if (pipex[i].path != NULL)
			free(pipex[i].path);
		if (pipex[i].str_path != NULL)
			free(pipex[i].str_path);
		if (pipex[i].fake_env)
			free_char_double(pipex[i].fake_env);
		if (pipex[i].env)
			free_char_double(pipex[i].env);
		i++;
	}
	free(pipex);
}

void	free_char_double(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
