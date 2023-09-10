/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/06 12:03:21 by ayael-ou         ###   ########.fr       */
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

void	create_every_files(char **files)
{
	int		fd_files;
	int		i;

	if (files == NULL)
		return ;
	i = 0;
	while (files[i])
	{
		fd_files = open(files[i], O_CREAT | O_TRUNC, 0666);
		close(fd_files);
		i++;
	}
}
