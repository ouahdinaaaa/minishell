/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:38:28 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/17 23:38:28 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	**add_export(char **env_cpy)
{
	int		i;
	char	*str1;
	int		new_len;
	char	*new_str;
	char	**new_env;

	i = 0;
	new_len = 0;
	new_env = malloc(sizeof(char *) * (size_of_env(env_cpy) + 1));
	while (env_cpy[i])
	{
		str1 = malloc(sizeof(char) * ft_strlen(env_cpy[i]) + 1);
		str1 = ft_strcpy(str1, env_cpy[i]);
		new_len = ft_strlen(str1) + strlen("export ") + 1;
		new_str = malloc(sizeof(char) * (new_len) + 1);
		if (new_str)
		{
			new_str = ft_strcpy(new_str, "export ");
			new_env[i] = ft_strjoin(new_str, str1);
			free(new_str);
			free(str1);
		}
		i++;
	}
	return (new_env[i] = NULL, new_env);
}

char	*copy1(char *str)
{
	int		i;
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(str) + 3));
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			res[i] = str[i];
			res[i + 1] = '"';
			i++;
			break ;
		}
		res[i] = str[i];
		i++;
	}
	res[i + 1] = '\0';
	return (res);
}

char	*copy2(char *str)
{
	char		*str2;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	j++;
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[j])
	{
		str2[i] = str[j];
		i++;
		j++;
	}
	str2[i] = '"';
	str2[i + 1] = '\0';
	return (str2);
}

char	**replace_export(char **env, int i)
{
	char	*str[2];
	char	**new_str;
	char	*join;

	new_str = malloc(sizeof(char *) * (size_of_env(env) + 100));
	while (env[i])
	{
		str[0] = copy1(env[i]);
		str[1] = copy2(env[i]);
		new_str[i] = malloc(sizeof(char)
				* (ft_strlen(str[0]) + ft_strlen(str[1]) + 1));
		if (new_str[i])
		{
			join = ft_strjoin(str[0], str[1]);
			if (join)
			{
				new_str[i] = ft_strcpy(new_str[i], join);
				free(join);
			}
			free(str[0]);
			free(str[1]);
		}
		i++;
	}
	return (new_str[i] = NULL, free_char_double(env), new_str);
}
