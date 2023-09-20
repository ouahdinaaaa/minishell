/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 07:49:04 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/11 07:49:04 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	swap_infinie(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

void	sort_env(char ***env, int size, int index)
{
	int	j;

	if (index >= size - 1)
		return ;
	j = 0;
	while (j < size - index - 1)
	{
		if (strcmp((*env)[j], (*env)[j + 1]) > 0)
			swap_infinie(&(*env)[j], &(*env)[j + 1]);
		j++;
	}
	sort_env(env, size, index + 1);
}

void	sort_new_env(char ***env, int size, int index)
{
	int	j;

	if (index >= size - 1)
		return ;
	j = 0;
	while (j < size - index - 1)
	{
		if (strcmp((*env)[j], (*env)[j + 1]) > 0)
			swap_infinie(&(*env)[j], &(*env)[j + 1]);
		j++;
	}
	sort_new_env(env, size, index + 1);
}

char	**export_fake_env(char **env)
{
	char	**env_copy;

	env_copy = add_export(env);
	env_copy = replace_export(env_copy, 0);
	sort_env(&env_copy, size_of_env(env_copy), 0);
	return (env_copy);
}

void	init_fake_env(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		pipex[i].fake_env = ft_strcpy_double(env);
		i++;
	}
}
