/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/13 03:16:43 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	size_nb(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	char	*num;
	int		len;

	len = size_nb(nb);
	num = malloc(sizeof(char) * (len + 1));
	num[len] = '\0';
	len--;
	if (nb == 0)
		num[len] = (nb % 10) + '0';
	while (nb > 0)
	{
		num[len] = (nb % 10) + '0';
		len--;
		nb /= 10;
	}
	return (num);
}

int	size_of_cmd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	create_every_files(t_pipex *pipex)
{
	int		fd_files;
	int		i;
	int		j;

	i = 0;
	if (!pipex[0].nboutfiles)
		return ;
	while (i < pipex[0].size)
	{
		j = 0;
		while (pipex[i].outfiles[j] && pipex[i].outfiles[j] != NULL)
		{
			fd_files = open(pipex[i].outfiles[j], O_CREAT | O_TRUNC, 0666);
			close(fd_files);
			j++;
		}
		i++;
	}
}
