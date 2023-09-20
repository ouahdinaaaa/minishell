/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_form_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:44:35 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/11 09:44:35 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*replace_light(t_pipex *pipex, char **next)
{
	char	*str3;
	char	*tmp;
	char	*str2;
	char	*join;

	if (next[0][0] == '*')
	{
		next[0] = delete_char(next[0]);
		str3 = search_and_replace(next[0], pipex);
		join = malloc(sizeof(char) * (ft_strlen(str3) + 1));
		join = ft_strcpy(join, str3);
		str2 = ft_add_quote(next[0]);
		if (join)
			tmp = ft_strjoin_all(join, str2);
		else
		{
			tmp = malloc(sizeof(char) * (ft_strlen(str2) + 1));
			tmp = ft_strcpy(tmp, str2);
		}
		free_files(join, str2, str3);
		join = malloc(sizeof(char) * ft_strlen(tmp) + 1);
		join = ft_strcpy(join, tmp);
		return (free(tmp), join);
	}
	return (NULL);
}

char	*replace_all(t_pipex *pipex, char *str, int status)
{
	char	**next;
	char	*join;
	char	*str1;
	int		i;

	i = 1;
	join = NULL;
	str1 = NULL;
	next = double_cut(str);
	if (next[0][0] == '*' && next[0][1] == '?')
		join = replace_status_doll(next, status);
	else if (next[0][0] == '*')
		join = replace_light(pipex, next);
	else
		join = replace_no_env(next);
	i = 1;
	while (next[i])
	{
		str1 = ft_strjoin_gnl(join, next[i]);
		join = malloc(sizeof(char) * (ft_strlen(str1) + 1));
		join = ft_strcpy(join, str1);
		free(str1);
		i++;
	}
	return (free_char_double(next), join);
}

char	*replace_no_env(char **next)
{
	char	*join;
	char	*str2;

	join = malloc(sizeof(char) * (ft_strlen(next[0]) + 2));
	str2 = add_dollar(next[0]);
	join = ft_strcpy(join, str2);
	free(str2);
	return (join);
}

char	*replace_status_doll(char **next, int status)
{
	char	*str2;
	char	*join;

	str2 = ft_replace_status(status, next[0]);
	join = malloc(sizeof(char) * (ft_strlen(str2) + 1));
	join = ft_strcpy(join, str2);
	free(str2);
	return (join);
}
