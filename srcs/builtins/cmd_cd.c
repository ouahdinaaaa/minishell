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

int	cmd_cd(char *path)
{
	if (chdir(path) == -1)
	{
		path = ft_strjoin("💕\033[38;2;0;204;0mcd :", path);
		path = ft_strjoin(path, 
				"\033[31m No such file or directory 💕\n");
		ft_putstr_fd(path, 2);
		return (1);
	}
	return (0);
}
