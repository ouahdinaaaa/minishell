/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars_here_doc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 06:01:58 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 06:01:58 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*return_fonct(char **new_str, char *src, char *str)
{
	free_char_double(new_str);
	free(src);
	src = malloc(sizeof(char) * (ft_strlen(str) + 1));
	src = ft_strcpy(src, str);
	return (src);
}

char	*replace_str_here(char *src, int status, t_pipex *pipex)
{
	char		**new_str;
	char		*str[2];
	int			i;

	i = 0;
	str[0] = NULL;
	if (src && detect_dollar(src))
	{
		new_str = ft_split(src, '$');
		if (detect_dollar(src) == 2)
		{
			i = 1;
			str[0] = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str[0] = ft_strcpy(str[0], new_str[0]);
		}
		while (new_str[i])
		{
			str[1] = replace_every(new_str[i], status, pipex);
			str[0] = ft_strjoin_str2(str[0], str[1]);
			i++;
		}
		src = return_fonct(new_str, src, str[0]);
	}
	return (src);
}

char	*replace_env_all(t_pipex *pipex, char **next)
{
	char	*join;
	char	*str3;
	char	*str2;
	char	*tmp;

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
	free_files(str2, join, str3);
	join = malloc(sizeof(char) * ft_strlen(tmp) + 1);
	join = ft_strcpy(join, tmp);
	free(tmp);
	return (join);
}

char	*replace_every(char *str, int status, t_pipex *pipex)
{
	char	**next;
	char	*join;
	char	*str1;
	int		i;

	i = 1;
	join = NULL;
	str1 = NULL;
	next = double_cut(str);
	if (next[0][0] == '?')
		replace_status_doll(next, status);
	else if (next[0])
		join = replace_env_all(pipex, next);
	while (next[i])
	{
		str1 = ft_strjoin(join, next[i]);
		free(join);
		join = malloc(sizeof(char) * (ft_strlen(str1) + 1));
		join = ft_strcpy(join, str1);
		free(str1);
		i++;
	}
	return (free_char_double(next), join);
}
