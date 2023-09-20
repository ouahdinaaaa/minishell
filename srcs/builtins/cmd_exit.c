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

int	verif_is_num(char *str)
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

void	new_condition(char *str1, char *str2, char **arg, t_pipex *pipex)
{
	int	nb;
	int	num;

	nb = 0;
	if (arg[1])
		num = verif_is_num(arg[1]);
	if (str2 && !num)
		write(STDERR_FILENO, "exit : too many arguments\n", 27);
	else if (str1 && !str2)
	{
		nb = ft_atoi(str1) % 256;
		write(STDERR_FILENO, "exit\n", 6);
		free_pipex(pipex);
		free_char_double(arg);
		exit(nb);
	}
}

void	situation_one(t_pipex *pipex, char *str)
{
	int		num;
	char	*str2;
	char	**arg;

	num = 0;
	if (!verif_str(str) && pipex[0].size == 1)
		exit(0);
	arg = ft_split(str, ' ');
	if (arg[1])
		num = verif_is_num(arg[1]);
	if (num && arg[1])
	{
		str2 = add_write_str("minishell : exit : ", arg[1],
				" : numeric argument required\n", "");
		write(STDERR_FILENO, str2, ft_strlen(str2));
		free(str2);
		free_pipex(pipex);
		free_char_double(arg);
		exit(2);
	}
	new_condition(arg[1], arg[2], arg, pipex);
	free_char_double(arg);
}

int	cmd_exit(t_pipex *builtins, int i)
{
	situation_one(builtins, builtins[i].cmd);
	return (1);
}
