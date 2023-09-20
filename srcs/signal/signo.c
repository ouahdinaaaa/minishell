/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:14:17 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/20 15:51:39 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ctrl_c_signo;

void	signal_ctrl_d(void)
{
	printf(GREEN"exit 👋 \n"RESET);
	exit(0);
}

void	signal_ctrl_slash(int signo)
{
	if (signo == SIGQUIT)
	{
		dprintf(2, "open in here\n");
	}
	// dprintf(2, "open\n");
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	signal_ctrl_c(int signo)
{

	if (signo == SIGINT)
	{
		// dprintf(2, "open in here\n");
		ctrl_c_signo = 130;
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
