/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:57:46 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/07/06 10:57:46 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	valid_print(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	print_verif(t_pipex *builtins)
{
	int	i;

	i = 0;
	while (i < builtins[0].size)
	{
		print_env(builtins[i].env);
		printf("\n\n\n");
		i++;
	}
}

void	free_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	size_of_env(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!*env || !env)
		return (0);
	while (env[i] && env[i] != NULL)
	{
		len++;
		i++;
	}
	return (len);
}

void	print_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		dprintf(2, "str_path : [%s]\n", pipex[i].str_path);
		dprintf(2, "delim : [%s]\n", pipex[i].delimiteur);
		dprintf(2, "files0 : [%s]\n", pipex[i].files[0]);
		dprintf(2, "files[1] : [%s]\n", pipex[i].files[1]);
		dprintf(2, "cmd : [%s]\n", pipex[i].cmd);
		dprintf(2, "path : [%s]\n", pipex[i].path);
		dprintf(2, "export : [%d]\n", pipex[i].export_cmd);
		dprintf(2, "dollar : [%d]\n", pipex[i].dollar);
		dprintf(2, "size : [%d]\n", pipex[i].size);
		dprintf(2, "pwd : [%d]\n", pipex[i].pwd);
		dprintf(2, "in : [%d]\n", pipex[i].in);
		dprintf(2, "here_doc : [%d]\n", pipex[i].here_doc);
		dprintf(2, "out : [%d]\n", pipex[i].out);
		dprintf(2, "erreur : [%d]\n", pipex[i].erreur);
		dprintf(2, "append : [%d]\n", pipex[i].append);
		dprintf(2, "cd : [%d]\n", pipex[i].cd);
		dprintf(2, "exit : [%d]\n", pipex[i].exit);
		dprintf(2, "echo : [%d]\n", pipex[i].echo);
		dprintf(2, "echo_n : [%d]\n", pipex[i].echo_n);
		dprintf(2, "unset : [%d]\n", pipex[i].unset);
		i++;
	}
}