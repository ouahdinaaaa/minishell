/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:53:48 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 17:53:48 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	cmd_pwd(void)
{
	char	*pwd = NULL;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("👣 %s\n", pwd);
	else
		printf(RED"pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"RESET);
	if (pwd)
		free(pwd);
	return (1);
}

char	*get_directory(char *pwd)
{
	char	*str;
	int		len;
	int		i;

	i = ft_strlen(pwd);
	while (i > 0)
	{
		if (pwd[i] == '/')
			break ;
		i--;
	}
	i++;
	str = malloc(sizeof(char) * ((ft_strlen(pwd) - i) + 3));
	len = 0;
	while (pwd[i] && pwd[i + 1])
	{
		str[len] = pwd[i];
		len++;
		i++;
	}
	str[len] = pwd[i];
	str[len + 1] = '>';
	str[len + 2] = ' ';
	str[len + 3] = '\0';
	return (str);
}

char	*print_directory(char **new_env, char *pwd)
{
	(void)new_env;
	char	*directory = NULL;
	char	*pwd2 = NULL;
	char	*fin =  NULL;

	pwd2 = getcwd(NULL, 0);
	if (pwd2)
	{
		directory = get_directory(pwd2);
		//dprintf(2, "str : [%s]\n", directory);
		fin = add_write_str(("\033[35m⚜️  "), directory, "\033[1;97m", "");
		free(directory);
		free(pwd);
		free(pwd2);
		//dprintf(2, "prompt ; [%s]\n", fin);
		return (fin);
	}
	return (pwd);
}

