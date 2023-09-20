/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:58:18 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/20 18:19:44 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	free_dataa(t_cmd *data)
{
	if (data->pids)
		free(data->pids);
	if (data)
		free(data);
}

int	ft_strncmp_here(char *s1, char *s2, size_t n, int nb)
{
	size_t	i;

	i = 0;
	if ((n <= 0 || (ft_strlen(s1) != (ft_strlen(s2) - 1))) && nb)
		return (1);
	if (!nb)
	{
		if (ft_strlen(s1) != ft_strlen(s2)
			|| (!s2 && ft_strlen(s1) != ft_strlen(s2)))
			return (1);
		while ((s1[i] && s2[i]) && s1[i] == s2[i])
			i++;
		return (s1[i] - s2[i]);
	}
	i = 0;
	while (s1[i] == s2[i] && i < n - 1 && nb)
		i++;
	return (s1[i] - s2[i]);
}

void	ft_ctrl_here(char *limiteur)
{
	char	*dest;

	dest = add_write_str("minishell : warning : ",
			"here_document at line by end_of_file (wanted '",
			limiteur, "')\n");
	write(STDERR_FILENO, dest, ft_strlen(dest));
	free(dest);
}

void	signal_ctrl_c_here(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	ctrl_c_signo = 120;
	//exit(130);
	//close(0);
}

void	delete_here_doc(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		if (pipex[i].here_doc)
			unlink(pipex[i].files[0]);
		i++;
	}
}
