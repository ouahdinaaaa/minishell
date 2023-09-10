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

char	*ft_strcpy(char *dest, const char *src)
{
	char	*d;

	d = dest;
	while (*src != '\0')
		*d++ = *src++;
	*d = '\0';
	return (dest);
}

char	*strcpySpecial(char *src, char deli, t_pipex *pipex, int *tab)
{
	int		length;
	int		i;
	int		j;
	char	*destination;
	(void)	deli;

	length = 0;
	j = 0;
	i = tab[0];
	while (src[i] && src[i] != deli)
	{
		i++;
		length++;
	}
	destination = (char *)malloc((length + 1) * sizeof(char));
	if (destination == NULL)
		return (NULL);
	i = tab[0];
	while (src[i] && j < length)
	{
		destination[j] = src[i++];
		pipex[tab[1]].index_char = pipex[tab[1]].index_char + 1;
		j++;
	}
	destination[length] = '\0';
	return (destination);
}

char	*strcpySpecialDq(char *src, t_pipex *pipex, int *tab)
{
	int		length;
	int		i;
	int		j;
	char	*destination;

	length = 1;
	j = 0;
	i = tab[0];
	pipex[tab[1]].sq++;
	while ((src[i] != '\0') && (src[i] == '\"'))
	{
		if (src[i] == '\"')
			pipex[tab[1]].dq++;
		length++;
		i++;
	}
	while ((src[i] != '\0') && pipex[tab[1]].sq != 0 && src[i] != '\"')
	{
		if (src[i + 1] == '\"')
			pipex[tab[1]].dq--;
		length++;
		i++;
	}
	length++;
	destination = (char *)malloc((length + 1) * sizeof(char));
	if (destination == NULL)
		return (NULL);
	i = tab[0] - 1;
	while (j < length)
	{
		destination[j] = src[i++];
		pipex[tab[1]].index_char = pipex[tab[1]].index_char + 1;
		j++;
	}
	destination[length] = '\0';
	pipex[tab[1]].index_char = pipex[tab[1]].index_char - 1;
	return (destination);
}

char	*strcpySpecialSq(char *src, t_pipex *pipex, int *tab)
{
	int		length;
	int		i;
	int		j;
	char	*destination;

	length = 1;
	j = 0;
	i = tab[0];
	pipex[tab[1]].sq++;
	while ((src[i] != '\0') && (src[i] == '\''))
	{
		if (src[i] == '\'')
			pipex[tab[1]].sq++;
		length++;
		i++;
	}
	while ((src[i] != '\0') && pipex[tab[1]].sq != 0 && src[i] != '\'')
	{
		if (src[i + 1] == '\'')
			pipex[tab[1]].sq--;
		length++;
		i++;
	}
	length++;
	destination = (char *)malloc((length + 1) * sizeof(char));
	if (destination == NULL)
		return (NULL);
	i = tab[0] - 1;
	while (j < length)
	{
		destination[j] = src[i++];
		pipex[tab[1]].index_char = pipex[tab[1]].index_char + 1;
		j++;
	}
	destination[length] = '\0';
	pipex[tab[1]].index_char = pipex[tab[1]].index_char - 1;
	return (destination);
}

void	displayPipex(t_pipex *pipex, int parts)
{
	int	i;

	i = 0;
	while (i < parts)
	{
		printf("\n\n   pipex[%d].in          = %d ", i, pipex[i].in);
		printf("\n   pipex[%d].out         = %d ", i, pipex[i].out);
		printf("\n   pipex[%d].files[0]    = %s ", i, pipex[i].files[0]);
		printf("\n   pipex[%d].files[1]    = %s ", i, pipex[i].files[1]);
		printf("\n   pipex[%d].here_doc    = %d ", i, pipex[i].here_doc);
		printf("\n   pipex[%d].delimiteur  = %s ", i, pipex[i].delimiteur);
		printf("\n   pipex[%d].append      = %d ", i, pipex[i].append);
		printf("\n   pipex[%d].cmd         = %s ", i, pipex[i].cmd);
		printf("\n   pipex[%d].size        = %d ", i, pipex[i].size);
		printf("\n   pipex[%d].export_cmd  = %d ", i, pipex[i].export_cmd);
		printf("\n   pipex[%d].pwd         = %d ", i, pipex[i].pwd);
		printf("\n   pipex[%d].cd          = %d ", i, pipex[i].cd);
		printf("\n   pipex[%d].exit        = %d ", i, pipex[i].exit);
		printf("\n   pipex[%d].echo        = %d ", i, pipex[i].echo);
		printf("\n   pipex[%d].echo_n      = %d ", i, pipex[i].echo_n);
		printf("\n   pipex[%d].envi        = %d ", i, pipex[i].envi);
		printf("\n   pipex[%d].path        = %s ", i, pipex[i].path);
		printf("\n   pipex[%d].unset       = %d ", i, pipex[i].unset);
		printf("\n   pipex[%d].erreur      = %d ", i, pipex[i].erreur);
		printf("\n   pipex[%d].str_path    = %s \n\n", i, pipex[i].str_path);
		i++;
	}
}

void	displayPipexEssential(t_pipex *pipex, int parts)
{
	int	i;

	i = 0;
	while (i < parts)
	{
		if (i == 0)
			printf("\n\n________________________________\n");
		if (pipex[i].in != 0)
			printf("\n   pipex[%d].in          = [%d] ", i, pipex[i].in);
		if (pipex[i].out != 0)
			printf("\n   pipex[%d].out         = [%d] ", i, pipex[i].out);
		if (pipex[i].files[0] != NULL)
			printf("\n   pipex[%d].files[0]    = [%s] ", i, pipex[i].files[0]);
		if (pipex[i].files[1] != NULL)
			printf("\n   pipex[%d].files[1]    = [%s] ", i, pipex[i].files[1]);
		if (pipex[i].here_doc != 0)
			printf("\n   pipex[%d].here_doc    = [%d] ", i, pipex[i].here_doc);
		if (pipex[i].delimiteur != NULL)
			printf("\n   pipex[%d].delimiteur  = [%s] ", i, pipex[i].delimiteur);
		if (pipex[i].append != 0)
			printf("\n   pipex[%d].append      = [%d] ", i, pipex[i].append);
		if (pipex[i].cmd != NULL)
			printf("\n   pipex[%d].cmd         = [%s] ", i, pipex[i].cmd);
		if (pipex[i].size != 0)
			printf("\n   pipex[%d].size        = [%d] ", i, pipex[i].size);
		if (pipex[i].export_cmd != 0)
			printf("\n   pipex[%d].export_cmd  = [%d] ", i, pipex[i].export_cmd);
		if (pipex[i].pwd != 0)
			printf("\n   pipex[%d].pwd         = [%d] ", i, pipex[i].pwd);
		if (pipex[i].cd != 0)
			printf("\n   pipex[%d].cd          = [%d] ", i, pipex[i].cd);
		if (pipex[i].exit != 0)
			printf("\n   pipex[%d].exit        = [%d] ", i, pipex[i].exit);
		if (pipex[i].echo != 0)
			printf("\n   pipex[%d].echo        = [%d] ", i, pipex[i].echo);
		if (pipex[i].echo_n != 0)
			printf("\n   pipex[%d].echo_n      = [%d] ", i, pipex[i].echo_n);
		if (pipex[i].envi != 0)
			printf("\n   pipex[%d].envi        = [%d] ", i, pipex[i].envi);
		if (pipex[i].path != NULL)
			printf("\n   pipex[%d].path        = [%s] ", i, pipex[i].path);
		if (pipex[i].unset != 0)
			printf("\n   pipex[%d].unset       = [%d] ", i, pipex[i].unset);
		if (pipex[i].erreur != 0)
			printf("\n   pipex[%d].erreur      = [%d] ", i, pipex[i].erreur);
		if (pipex[i].str_path != NULL)
			printf("\n   pipex[%d].str_path    = [%s] ", i, pipex[i].str_path);
		printf("\n________________________________\n\n");
		i++;
	}
}