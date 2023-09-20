/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:00:07 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/11 13:00:07 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	end_function_cmd(char **new_str, t_pipex *pipex, char *str)
{
	free_char_double(new_str);
	free(pipex->cmd);
	pipex->cmd = malloc(sizeof(char) * (ft_strlen(str) + 1));
	pipex->cmd = ft_strcpy(pipex->cmd, str);
	free(str);
}

void	end_function_path(char **new_str, t_pipex *pipex, char *str)
{
	free_char_double(new_str);
	free(pipex->path);
	pipex->path = malloc(sizeof(char) * (ft_strlen(str) + 1));
	pipex->path = ft_strcpy(pipex->path, str);
	free(str);
}

void	end_function_files_in(char **new_str, t_pipex *pipex, char *str)
{
	free_char_double(new_str);
	free(pipex->files[0]);
	pipex->files[0] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	pipex->files[0] = ft_strcpy(pipex->files[0], str);
	free(str);
}

void	end_function_files_out(char **new_str, t_pipex *pipex, char *str)
{
	free_char_double(new_str);
	free(pipex->files[1]);
	pipex->files[1] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	pipex->files[1] = ft_strcpy(pipex->files[1], str);
	free(str);
}

void	end_function_limiteur(char **new_str, t_pipex *pipex, char *str)
{
	free_char_double(new_str);
	free(pipex->delimiteur);
	pipex->delimiteur = malloc(sizeof(char) * (ft_strlen(str) + 1));
	pipex->delimiteur = ft_strcpy(pipex->delimiteur, str);
	free(str);
}
