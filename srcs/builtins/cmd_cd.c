/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:12 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 17:51:12 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*retrieve_home(char **new_env)
{
	int	i;
	int	place;

	i = 0;
	place = 0;
	while (new_env[i])
	{
		place = find_end_path(new_env[i]);
		if (!ft_strncmp(new_env[i], "HOME", (place)) && new_env[i][place] == '=')
			return (new_env[i] + 5);
		i++;
	}
	return (NULL);
}

int	cmd_cd(char *path, char **env)
{
	char	*str;
	char	*solo;

	str = NULL;
	solo = retrieve_home(env);
	if (!path && solo)
		return (chdir(solo), 1);
	if (!path && !solo)
	{
		str = add_write_str("\033[34mbash : cd: ", "HOME",
				" \033[31m:", "not set\n");
		write(STDERR_FILENO, str, ft_strlen(str));
		return (free(str), 1);
	}
	else if (path[0] == '~' && path[1] == '\0')
		return (chdir("/mnt/nfs/homes/ayael-ou"), 1);
	if (chdir(path) == -1)
	{
		str = ft_strjoin("📁 \033[38;2;0;204;0mcd :", path);
		str = ft_strjoin_gnl(str,
				"\033[31m No such file or directory 📁\n");
		ft_putstr_fd(str, 2);
		return (free(str), 1);
	}
	return (0);
}
