/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-forms2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:14:24 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/13 03:04:46 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
	create_every_files(pipex);
	while (i < pipex[0].size)
	{
		if (pipex[i].erreur && pipex[i].erreur != -1)
			return (pipex[i].erreur);
		else if (pipex[0].cmd == NULL || !pipex[0].cmd)
			return (pipex[i].erreur = 0, 12);
		i++;
	}
	return (0);
}

char	*new_str_special(char *src)
{
	char	*str;
	int		i;
	int		j;

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
