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

char	*replace_str_here(char *src, int status, t_pipex *pipex)
{
	char		**new_str;
	char		*str;
	char		*join;
	int			i;

	i = 0;
	str = NULL;
	if (src && detect_dollar(src))
	{
		new_str = ft_split(src, '$');
		if (detect_dollar(src) == 2)
		{
			i = 1;
			str = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str = ft_strcpy(str, new_str[0]);
		}
		while (new_str[i])
		{
			join = replace_every(new_str[i], status, pipex);
			str = ft_strjoin_gnl(str, join);
			free(join);
			i++;
		}
		free_char_double(new_str);
		free(src);
		src = malloc(sizeof(char) * (ft_strlen(str) + 1));
		src = ft_strcpy(src, str);
		free(str);
	}
    return (src);
}

char	*replace_every(char *str, int status, t_pipex *pipex)
{
	char	**next;
	char	*tmp = NULL;
	char	*join = NULL;
	char	*str2 = NULL;
	char	*str3 = NULL;
	char	*str1 = NULL;
	int		i;

	i = 1;
	next = double_cut(str);
	if (next[0][0] == '?')
	{
		str2 = ft_replace_status(status, next[0]);
		join = malloc(sizeof(char) * (ft_strlen(str2) + 1));
		join = ft_strcpy(join, str2);
		free(str2);
	}
	else if (next[0])
	{
		str3 = search_and_replace(next[0], pipex);
		join = malloc(sizeof(char) * (ft_strlen(str3)+ 1));
		join = ft_strcpy(join, str3);
		str2 = ft_add_quote(next[0]);
		if (join)
			tmp = ft_strjoin_all(join, str2);
		else 
		{
			tmp = malloc(sizeof(char) * (ft_strlen(str2) + 1));
			tmp = ft_strcpy(tmp, str2);
		}
		if (join)
			free(join);
		if (str2)
			free(str2);
		if (str3)
			free(str3);
		join = malloc(sizeof(char) * ft_strlen(tmp) + 1);
		join = ft_strcpy(join, tmp);
		free(tmp);
	}
	else
	{
		join = malloc(sizeof(char) * (ft_strlen(next[0]) + 2));
		str2 = add_dollar(next[0]);
		join = ft_strcpy(join, str2);
		free(str2);
	}
	i = 1;
	while (next[i])
	{
		str1 = ft_strjoin(join, next[i]);
		free(join);
		join = malloc(sizeof(char) * (ft_strlen(str1) + 1));
		join = ft_strcpy(join, str1);
		free(str1);
		i++;
	}
	free_char_double(next);
	return (join);
}

// int	main(int argc, char	**argv, char **env)
// {
// 	(void)argc;
// 	(void)env;
// 	(void)argv;
// 	t_pipex *pipex;
// 	char	*str = NULL;

// 	if (argc != 2)
// 		return (printf("argument !!!\n"), 1);
// 	(void)pipex;

// 	pipex = malloc(sizeof(t_pipex) * 1);
// 	pipex[0].size = 1;
// 	pipex[0].cmd = NULL;
// 	pipex[0].path = NULL;
// 	pipex[0].files[0] = NULL;
// 	pipex[0].files[1] = NULL;
// 	str = malloc(sizeof(char) * (ft_strlen(argv[1]) + 1));
// 	str = ft_strcpy(str, argv[1]);
// 	dprintf(2, "argv : [%s]\n", str);
// 	pipex[0].env = ft_strcpy_double(env);
// 	str = replace_str_here(str, 4, pipex);
// 	dprintf(2, "replace : [%s]\n", str);
// 	free_char_double(pipex[0].env);
// 	free(str);
// 	free(pipex);
// }
