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

int	choice_of_builtins(t_pipex *built, int i)
{
	int	res;

	res = 0;
	if (built[i].cd == 1 && built[i].size == 1)
		res = cmd_cd(built[i].path);
        else if (built[i].cd == 2)
                ft_putstr_fd("cd: too many arguments\n", 2);
	else if (built[i].pwd)
		res = cmd_pwd();
	else if (built[i].exit)
		res = cmd_exit(built, i);
	else if (built[i].echo)
		res = cmd_echo(built[i].str_path, built[i].echo_n);
	else if (built[i].envi)
		res = cmd_env(built[i].env);
	else if (built[i].unset && built[0].size == 1)
		res = cmd_unset(&built[i], built);
	else if (built[i].export_cmd && (built[0].size == 1 || !built[i].str_path))
                res = cmd_export(&built[i], built, i);
	else if (built[i].cd == 1 || built[i].unset || built[i].export_cmd)
		res = 1;
	if (res && built[i].size != 1)
		exit(0);
        return (res);
}

/*
        BUILTINS FAIT :
        create tableau de builtin
        tab[i] = nom de commande
        tab[i][j] = argument à envoyer

    - CD
    - PWD
    - EXIT pour le builtin exit, après avoir fait
    mainte et mainte test exit avec | ne sert strictement à rien
    donc peut-être que tout ceci sert à exit


    pas sur de mes dires, mais on dirais que l'execution des
    builtins se fait uniquement sans pipex ou peut-être le pwd
*/

/*
        COMMANDE AVEC PIPE
        -echo
        - env
        - export

        COMMANDE UTILISATION SANS PIPE
        - cd
        - pwd (voir on peux utiliser avec pipe)
        - unset

*/

/*
        ///// Fonction perfect //////

            - echo
            - pwd
            - cd
            - echo -n
*/
