/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtind.C                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:52:23 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 17:52:23 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	choice_of_builtins(t_pipex *built, int i, int status)
{
	int	res;

	res = 0;
	if (built[i].cd == 1 && built[i].size == 1)
		res = cmd_cd(built[i].path, built[i].env);
	else if (built[i].cd == 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (built[i].pwd)
		res = cmd_pwd();
	else if (built[i].exit)
		res = cmd_exit(built, i);
	else if (built[i].echo)
		res = cmd_echo(built[i].commande, built[i].echo_n, status, built);
	else if (built[i].envi)
		res = cmd_env(built[i].env);
	else if (built[i].unset && built[0].size == 1)
		res = cmd_unset(&built[i], built);
	else if (built[i].export_cmd && (built[0].size == 1 || !built[i].str_path))
		res = cmd_export(&built[i], built, i);
	else if (built[i].cd == 1 || built[i].unset || built[i].export_cmd)
		res = 1;
	//if (res && built[i].size != 1)
	//	return (free_pipex(built), exit(0), res);
	return (res);
}
