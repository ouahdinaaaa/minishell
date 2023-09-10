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
	char	pwd[2024];

	if (getcwd(pwd, sizeof(pwd)))
		printf("👣 %s\n", pwd);
	else
		printf(RED"Error of pwd\n"RESET);
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

char	*print_directory(void)
{
	char	*directory; 
	char	pwd[2024];
	char	*result;
	char	*fin;

	getcwd(pwd, sizeof(pwd));
	directory = get_directory(pwd);
	fin = ft_strjoin(("\033[35m⚜️  "), directory);
	free(directory);
	result = ft_strjoin(fin, RESET);
	free(fin);
	return (result);
}
