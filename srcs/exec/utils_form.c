/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_form.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:16:35 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/05 18:16:35 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*replace_env(t_pipex *pipex, int i, int j, char *str2)
{
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(pipex->env[i]) + 1);
	str = ft_strcpy(str, pipex->env[i] + (j + 1));
	if (str2)
		return (ft_strjoin_str2(str, str2));
	return (str);
}

char	*search_and_replace(char *str, t_pipex *pipex)
{
	int		tab[3];
	char	*str2;

	str2 = NULL;
	tab[1] = size_path(str);
	tab[2] = tab[1];
	if (tab[2] == -1)
		tab[2] = (ft_strlen(str));
	tab[0] = 0;
	str2 = new_str_special(str);
	while (pipex->env[tab[0]])
	{
		if (tab[2] == 0)
			break ;
		if (!ft_strncmp(str, pipex->env[tab[0]], tab[2])
			&& pipex->env[tab[0]][tab[2]] == '=')
			return (replace_env(pipex, tab[0], tab[2], str2));
		tab[0] += 1;
	}
	if (str2)
		return (str2);
	str = malloc(sizeof(char) * ft_strlen(str) + 1);
	return (str = ft_strcpy(str, "\0"), str);
}

// tab[0] == i   ||| tab[2] == j
