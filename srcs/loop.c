/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/20 17:58:02 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_my_env(void)
{
	char	*path = NULL;
	char	**new_env;

	path = getcwd(NULL, 0);
	new_env = malloc(sizeof(char *) * 2);
	new_env[0] = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen("OLDPWD=") + 2));
	new_env[0] = ft_strjoin("OLDPWD=", path);
	new_env[1] = NULL;
	return (new_env);
}

void	loop(char **env)
{
	t_pipex	*pipex;
	char	*commande;
	char	**new_env;
	int		status;
	char	**export;
	char	*pwd = NULL;

	commande = NULL;
	status = 0;
	if (!env || !*env)
		new_env = copy_my_env();
	else
		new_env = ft_strcpy_double(env);
	export = export_fake_env(new_env);
	// signal(SIGQUIT, signal_ctrl_slash);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c);
	while (1)
	{
		pwd = print_directory(new_env, pwd);
		commande = readline(pwd);
		if (commande == NULL)
		{
			free_char_double(new_env);
			free_char_double(export);
			free(commande);
			free(pwd);
			signal_ctrl_d();
		}
		if (commande != NULL && *commande)
		{
			if (ctrl_c_signo == 130)
			{
				status = 130;
				dprintf(2, "exit in here\n");
				//unlink(pipex[data.i].files[0]);
				//close(pipex[0].erreur);
				//exit(sta);
			}
			signal(SIGINT, SIG_IGN);
			ft_putstr_fd(SAPIN, 2);
			add_history(commande);
			pipex = init_pipex((ft_count_pipes(commande) + 1), new_env);
			parsing(commande, pipex, pipex[0].env);
			display_pipex(pipex, (pipex[0].size));
			free_char_double(new_env);
			init_fake_env(pipex, export);
			free_char_double(export);
			init_cmd(pipex, commande);
			status = pipex_main(pipex[0].env, pipex, status, pwd);
			new_env = ft_strcpy_double(pipex[0].env);
			export = export_fake_env(new_env);
			free_pipex(pipex);
			ft_putstr_fd(RESET, 2);
			ctrl_c_signo = 0;
		}
		free(commande);
		signal(SIGINT, signal_ctrl_c);
	}
}

// displayPipexEssential(pipex, (pipex[0].size));

/*
	**echo quand on a un chevrons retirer les simple auote du mot debut\fin + guilleme debut fin si ya
*/

/***				REverifer
..............................

revoir le test echo 'he"lo' retire aussi la double quuotte voir pourquoi
voir prblm avec echo si

renouvllement de mon fake export
***retire simple quote plus double quote
touch avec guillemets vide seegfault sur parsing
oublie des message erreur pour << et >> qund + 1chevron
..................................
*///proteger write + malloc + retour de fonction
// parsing pensee au echo -n -n -n -n
// ---> retirer tout les -n qui suivent echo peut importe espace
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind.txt ./minishell
// changer regler vraiment
// garbage collector ---> derniere necessite
