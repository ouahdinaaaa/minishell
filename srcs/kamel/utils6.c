/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/13 18:17:08 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*extractsubstring(char *str)
{
	char	*result;
	char	*dollarptr;
	size_t	length;

	result = NULL;
	dollarptr = ft_strchr(str, '$');
	if (dollarptr != NULL)
	{
		length = strlen(dollarptr + 1) + 1;
		result = (char *)malloc((length + 1) * sizeof(char));
		ft_strncpy(result, dollarptr, length);
		result[length] = '\0';
	}
	return (result);
}

void	bzero_pipex(int i, t_pipex *pipex)
{
	pipex[i].in = 0;
	pipex[i].out = 0;
	pipex[i].append = 0;
	pipex[i].size = 0;
	pipex[i].here_doc = 0;
	pipex[i].export_cmd = 0;
	pipex[i].pwd = 0;
	pipex[i].cd = 0;
	pipex[i].exit = 0;
	pipex[i].echo = 0;
	pipex[i].echo_n = 0;
	pipex[i].envi = 0;
	pipex[i].unset = 0;
	pipex[i].index_char = 0;
	pipex[i].erreur = 0;
	pipex[i].sq = 0;
	pipex[i].dq = 0;
}

int	checkOutfile(char *commande, int debut, t_pipex *pipex, int ip)
{
	int	i;

	i = debut;
	while (commande[i + 1])
	{
		if (commande[i + 1] != ' ')
		{
			return (1);
		}
		i++;
	}
	if (pipex[ip].erreur == 0)
		printf("\nerreur de syntaxe près du symbole inattendu « newline »\n");
	return (0);
}

int	checkFileAppend(char *commande, int debut, t_pipex *pipex, int ip)
{
	int	i;

	i = debut;
	while (commande[i + 1])
	{
		if (commande[i + 1] != ' ')
		{
			return (1);
		}
		i++;
	}
	if (pipex[ip].erreur == 0)
		printf("\nerreur de syntaxe près du symbole inattendu « newline »\n");
	return (0);
}

int	checkFileHeredoc(char *commande, int debut)
{
	int	i;

	i = debut;
	while (commande[i + 1])
	{
		if (commande[i + 1] == '>')
		{
			printf("\nerreur de syntaxe près du symbole inattendu « > »\n");
			return (0);
		}
		if (commande[i + 1] != ' ')
		{
			return (1);
		}
		i++;
	}
	printf("\nerreur de syntaxe près du symbole inattendu « newline »\n");
	return (0);
}