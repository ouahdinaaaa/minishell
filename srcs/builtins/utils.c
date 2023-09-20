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
	if (!*env || !env || env == NULL)
		return (0);
	while (env[i] && env[i] != NULL)
	{
		i++;
		len++;
	}
	return (len);
}
