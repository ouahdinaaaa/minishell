/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:54:04 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/05 17:54:04 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*add_dollar(char *str)
{
	int	i;
	char *str2;

	str2 = malloc(sizeof(char) * (ft_strlen(str) + 3));
	i = 0;
	str2[0] = '$'; 
	while (str[i])
	{
		str2[i + 1] = str[i];
		i++;
	}
	str2[i + 1] = '\0';
	return (str2);
}

void	replace_every_struct(t_pipex *pipex, int status)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		replace_files(&pipex[i], status);
		replace_out(&pipex[i], status); 
		replace_str_path(&pipex[i], status); 
		replace_path(&pipex[i], status);
		replace_str_cmd(&pipex[i], status);
		i++;
	}
}

void	replace_files(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str;
	char		*join;
	int			i;

	i = 0;
	if (pipex->files[0] && detect_dollar(pipex->files[0]))
	{
		new_str = ft_split(pipex->files[0], '$');
		if (detect_dollar(pipex->files[0]) == 2)
		{
			str = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			i = 1;
			str = ft_strcpy(str, new_str[0]);
		}
		while (new_str[i])
		{
			join =  replace_all(pipex, new_str[i], status);
			str = ft_strjoin_gnl(str, join);
			free(join);
			i++;
		}
		free_char_double(new_str);
		pipex->files[0] = malloc(sizeof(char) * (ft_strlen(str) + 1));
		pipex->files[0] = ft_strcpy(pipex->files[0], str);
		free(str);
	}
}

void	replace_out(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str;
	char		*join;
	int			i;

	i = 0;
	str = NULL;
	if (pipex->files[1] && detect_dollar(pipex->files[1]))
	{
		new_str = ft_split(pipex->files[1], '$');
		if (detect_dollar(pipex->files[1]) == 2)
		{
			i = 1;
			str = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str = ft_strcpy(str, new_str[0]);
		}
		while (new_str[i])
		{
			join = replace_all(pipex, new_str[i], status);
			str = ft_strjoin_gnl(str, join);
			free(join);
			i++;
		}
		free_char_double(new_str);
		free(pipex->files[1]);
		pipex->files[1] = malloc(sizeof(char) * (ft_strlen(str) + 1));
		pipex->files[1] = ft_strcpy(pipex->files[1], str);
		free(str);
	}
}

void	replace_str_path(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str;
	char		*join;
	int			i;

	i = 0;
	str = NULL;
	if (pipex->str_path && detect_dollar(pipex->str_path))
	{
		new_str = ft_split(pipex->str_path, '$');
		if (detect_dollar(pipex->str_path) == 2)
		{
			i = 1;
			str = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str = ft_strcpy(str, new_str[0]);
		}
		while (new_str[i])
		{
			join = replace_all(pipex, new_str[i], status);
			str = ft_strjoin_gnl(str, join);
			free(join);
			i++;
		}
		free_char_double(new_str);
		free(pipex->str_path);
		pipex->str_path = malloc(sizeof(char) * (ft_strlen(str) + 1));
		pipex->str_path = ft_strcpy(pipex->str_path, str);
		free(str);
	}
}

void	replace_path(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str;
	char		*join;
	int			i;

	i = 0;
	str = NULL;
	if (pipex->path && detect_dollar(pipex->path))
	{
		new_str = ft_split(pipex->path, '$');
		if (detect_dollar(pipex->path) == 2)
		{
			i = 1;
			str = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str = ft_strcpy(str, new_str[0]);
		}
		while (new_str[i])
		{
			join = replace_all(pipex, new_str[i], status);
			str = ft_strjoin_gnl(str, join);
			i++;
		}
		free_char_double(new_str);
		free(pipex->path);
		pipex->path = malloc(sizeof(char) * (ft_strlen(str) + 1));
		pipex->path = ft_strcpy(pipex->path, str);
		free(str);
	}
}

void	replace_str_cmd(t_pipex *pipex, int status)
{
	char		**new_str;
	char		*str;
	char		*join;
	int			i;

	i = 0;
	str = NULL;
	if (pipex->cmd && detect_dollar(pipex->cmd))
	{
		new_str = ft_split(pipex->cmd, '$');
		if (detect_dollar(pipex->cmd) == 2)
		{
			i = 1;
			str = malloc(sizeof(char) * (ft_strlen(new_str[0]) + 1));
			str = ft_strcpy(str, new_str[0]);
		}
		while (new_str[i])
		{
			join = replace_all(pipex, new_str[i], status);
			str = ft_strjoin_gnl(str, join);
			free(join);
			i++;
		}
		free_char_double(new_str);
		free(pipex->cmd);
		pipex->cmd = malloc(sizeof(char) * (ft_strlen(str) + 1));
		pipex->cmd = ft_strcpy(pipex->cmd, str);
		free(str);
	}
}

char	*delete_char(char *src)
{
	char	*str;
	int	i = 1;
	int	j = 0;

	str = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!str)
		return (NULL);
	while(src[i])
	{
		str[j] = src[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(src);
	return (str);
}

char	*replace_all(t_pipex *pipex, char *str, int status)
{
	(void)pipex;
	(void)str;
	(void)status;
	char	**next;
	char	*tmp = NULL;
	char	*join = NULL;
	char	*str2 = NULL;
	char	*str3 = NULL;
	char	*str1 = NULL;
	int		i;

	i = 1;
	next = double_cut(str);
	if (next[0][0] == '*' && next[0][1] == '?')
	{
		str2 = ft_replace_status(status, next[0]);
		join = malloc(sizeof(char) * (ft_strlen(str2) + 1));
		join = ft_strcpy(join, str2);
		free(str2);

	}
	else if (next[0][0] == '*')
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

// 	if (argc != 2)
// 		return (printf("argument !!!\n"), 1);
// 	(void)pipex;

// 	pipex = malloc(sizeof(t_pipex) * 1);
// 	pipex[0].size = 1;
// 	pipex[0].cmd = NULL;
// 	pipex[0].path = NULL;
// 	pipex[0].files[0] = NULL;
// 	pipex[0].files[1] = NULL;
// 	pipex[0].str_path = malloc(sizeof(char) * (ft_strlen(argv[1]) + 1));
// 	pipex[0].str_path = ft_strcpy(pipex[0].str_path, argv[1]);
// 	dprintf(2, "argv : [%s]\n", pipex[0].str_path);
// 	pipex[0].env = ft_strcpy_double(env);
// 	replace_every_struct(pipex, 4);
// 	dprintf(2, "replace : [%s]\n", pipex[0].str_path);
// 	free_char_double(pipex[0].env);
// 	free(pipex[0].str_path);
// 	free(pipex);
// }
