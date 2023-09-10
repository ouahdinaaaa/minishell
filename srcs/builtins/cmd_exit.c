/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:50:54 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 17:50:54 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	verif_str(char *str)
{
	int	i;

	i = 4;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return (1);
	return (0);
}

int verif_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

void	situation_one(t_pipex *pipex, char *str)
{
	char	**arg;
	int	num;
	int nb;
	char	*str2;

	(void)nb;
	num = 0;
	if (!verif_str(str) && pipex[0].size == 1)
		exit(0);
	arg = ft_split(str, ' ');
	if (arg[1])
		num = verif_is_num(arg[1]);
	if (num)
	{
		str2 = ft_strjoin("minishell : exit : ", arg[1]);
		str2 = ft_strjoin_gnl(str2, " : numeric argument required\n");
		ft_putstr_fd(str2 , 2);
		free(str2);
		free_pipex(pipex);
		free_char_double(arg);
		exit(2);
	}
	else if (arg[2] && !num)
		ft_putstr_fd("exit \nexit : too many arguments\n", 2);
	else if (arg[1] && !arg[2])
	{
		nb = ft_atoi(arg[1]) % 256;
		ft_putstr_fd("exit\n", 2);
		free_pipex(pipex);
		free_char_double(arg);
		exit(nb);
	}
	free_char_double(arg);
}

int	cmd_exit(t_pipex *builtins, int i)
{
	situation_one(builtins, builtins[i].cmd);
	return (1);
}
