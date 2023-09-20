/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:05:07 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/12 12:32:31 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*ft_strjoin_str2(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s2);
	free(s1);
	return (str);
}

int	verif_special(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (0);
	return (1);
}

int	size_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (verif_special(str[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_stradd(char *str, char *str2)
{
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 0;
	join = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(str2) + 1));
	while (str[i])
	{
		join[j] = str[i];
		i++;
		j++;
	}
	i = 0;
	while (str2[i])
	{
		join[j] = str2[i];
		i++;
		j++;
	}
	join[j] = '\0';
	free(str);
	free(str2);
	return (join);
}

char	*ft_add_quote(char *str)
{
	char	*str2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	while (str[i] != '\0')
	{
		str2[j] = str[i];
		j++;
		i++;
	}
	str2[j] = '\0';
	return (str2);
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
// 	pipex[0].str_path = NULL;
// 	pipex[0].files[0] = NULL;
// 	pipex[0].files[1] = NULL;
// 	dprintf(2, "argv : [%s]\n", argv[1]);
// 	pipex[0].str_path = malloc(sizeof(char) * (ft_strlen(argv[1]) + 1));
// 	pipex[0].str_path = ft_strcpy(pipex[0].str_path, argv[1]);
// 	pipex[0].env = ft_strcpy_double(env);
// 	replace_every_struct(pipex, 4);
// 	dprintf(2, "replace : [%s]\n", pipex[0].str_path);
// 	free_all_sep(pipex[0].env);
// 	free(str);
// 	free(pipex[0].str_path);
// 	free(pipex);
// }