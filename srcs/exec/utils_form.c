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

char	*ft_stradd(char *str, char *str2)
{
	int	i;
	int j;
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
	int	i;
	int	j;

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

int verif_special(char c)
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

char	*replace_str(char *cmd)
{
	char	*str;
	int		i;
	int		j;

	i = 1;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(cmd));
	while (cmd[i])
	{
		str[j] = cmd[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

int	error_syntaxe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		if (pipex[i].erreur && pipex[i].erreur != -1)
			return (pipex[i].erreur);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
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
	free(s1);
	return (str);
}

char	*new_str_special(char *src)
{
	char *str;
	int	i;
	int j;

	i = size_path(src);
	if (i == -1)
		return (NULL);
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src[i])
	{
		str[j] = src[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*search_and_replace(char *str, t_pipex *pipex)
{
	int	i;
	int	len_str;
	int	len;
	char	*str2 = NULL;

	len_str = size_path(str);
	len = len_str;
	if (len == -1)
		len = (ft_strlen(str));
	i = 0;
	str2 = new_str_special(str);
	while (pipex->env[i])
	{
		if (len == 0)
			break ;
		if (!ft_strncmp(str, pipex->env[i], len) && pipex->env[i][len] == '=')
		{
			str = malloc(sizeof(char) * ft_strlen(pipex->env[i]) + 1);
			str = ft_strcpy(str, pipex->env[i] + (len + 1));
			if (str2)
				return(ft_strjoin_str2(str, str2));
			return (str);
		}
		i++;
	}
	if (str2)
		return(str2);
	str = malloc(sizeof(char) * ft_strlen(str) + 1);
	str = ft_strcpy(str, "\0");
	return (str);
}
