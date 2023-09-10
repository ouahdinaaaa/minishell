/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/10 04:54:13 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop(char **env)
{
	t_pipex	*pipex;
	char	*commande;
	char	**new_env;
	int		status;
	char	**export;
	char	*pwd;

	commande = NULL;
	(void)status;
	new_env = ft_strcpy_double(env);
	export = export_fake_env(env);
	signal(SIGQUIT, signal_ctrl_slash);
	signal(SIGINT, signal_ctrl_c);
	while (1)
	{
		pwd = print_directory();
		commande = readline(pwd);
		if (commande == NULL)
		{
			free(pwd);
			free(commande);
			free_char_double(new_env);
			signal_ctrl_d();
		}
		if (commande != NULL && *commande)
		{
			if (ctrl_c_signo == 130)
				status = 130;
			signal(SIGINT, SIG_IGN);
			ft_putstr_fd(BLUE, 2);
			add_history(commande);
			pipex = init_pipex((countPipes(commande) + 1), new_env);
			parsing(commande, pipex, pipex[0].env);
			free_char_double(new_env);
			init_fake_env(pipex, export);
			displayPipexEssential(pipex, (pipex[0].size));
			status = pipex_main(pipex[0].env, pipex, status);
			new_env = ft_strcpy_double(pipex[0].env);
			free_pipex(pipex);
			ft_putstr_fd(RESET, 2);
			ctrl_c_signo = 0;
		}
		free(pwd);
		free(commande);
		signal(SIGINT, signal_ctrl_c);
	}
}

/*
	utilise ce main avec valgrind --leak-checl=full ./minishell avec une commande
	Quand taura aucun leaks ni rien aucune erreur utilise le dans minishell et voyons si ya tjrs prblm
*/

/*
	Update de ce que jai fait !

	** Heredoc si "limiter" on remplace pas le dollard
	** sinon si limiter on remplace le dollard
	si Ctrl+C fait dans minishell valeur de retour = 130
	Expand bien regler mtn le dollard il est bien remaplce et bonne valeur ajouté (skip les caractere speciaux)
	
*/


/*
		UPdate de ce qu'il me reste à faire

	** Leaks de zinzin avec unset 
	** verifier mon execcution a part avec valgrind --leak-check=full ./minishell
	+ verifier track fds que tout mes fd soit bien fermé.

	** Faire la norminette.
	** Retirer tout mes Dprintf voir si mettre que smiley et couleur uni [REGLER CE BIG SOUCIS]
	** Regler soucis dans $ si $****USER important  [fait]
	** Regler soucis $$ [fait]
	** REvoir le soucis du replace $ bien bien teste
	** courte replace


	PS : ON A LE MINISHELL LE PLUS JOLIE DE L'ECOLE
*/