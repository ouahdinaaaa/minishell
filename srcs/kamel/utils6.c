/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/19 14:28:17 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*initialdest;

	initialdest = dest;
	while (*src != '\0' && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}
	return (initialdest);
}

int	check_only_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	free_char_double(char **array)
{
	int	i;

	i = 0;
	if (!array || array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		// array[i] = NULL;
		i++;
	}
	free(array);
}

int	ft_count_dollars(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == '$')
			nb++;
		i++;
	}
	return (nb);
}
