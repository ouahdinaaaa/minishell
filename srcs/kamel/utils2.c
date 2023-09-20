/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:35:19 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*temp;

	temp = dest;
	while (*temp != '\0')
		temp++;
	while (*src != '\0')
	{
		*temp = *src;
		temp++;
		src++;
	}
	*temp = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*d;

	d = dest;
	while (*src != '\0')
		*d++ = *src++;
	*d = '\0';
	return (dest);
}

void	display_pipex(t_pipex *pipex, int parts)
{
	int	i;
	int	in;
	int out;

	i = 0;
	in = 0;
	out = 0;
	while (i < parts)
	{
		if (i == 0)
			printf("\n\n________________________________\n");
		if (pipex[i].in != 0)
			printf("\n   pipex[%d].in          = [%d] ", i, pipex[i].in);
		if (pipex[i].out != 0)
			printf("\n   pipex[%d].out         = [%d] ", i, pipex[i].out);
		if (pipex[i].files[0])
			printf("\n   pipex[%d].files[0]    = [%s] ", i, pipex[i].files[0]);
		if (pipex[i].files[1])
			printf("\n   pipex[%d].files[1]    = [%s] ", i, pipex[i].files[1]);
		if (pipex[i].here_doc != 0)
			printf("\n   pipex[%d].here_doc    = [%d] ", i, pipex[i].here_doc);
		if (pipex[i].delimiteur)
			printf("\n   pipex[%d].delimiteur  = [%s] ", i, pipex[i].delimiteur);
		if (pipex[i].append != 0)
			printf("\n   pipex[%d].append      = [%d] ", i, pipex[i].append);
		if (pipex[i].cmd)
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
		if (pipex[i].path)
			printf("\n   pipex[%d].path        = [%s] ", i, pipex[i].path);
		if (pipex[i].unset != 0)
			printf("\n   pipex[%d].unset       = [%d] ", i, pipex[i].unset);
		if (pipex[i].erreur != 0)
			printf("\n   pipex[%d].erreur      = [%d] ", i, pipex[i].erreur);
		if (pipex[i].str_path)
			printf("\n   pipex[%d].str_path    = [%s] ", i, pipex[i].str_path);
		if (pipex[i].infiles)
		{
			printf("\n   Tableau d'infiles    = [");
			in = 0;
			while (in < pipex[i].nbinfiles)
			{
				printf(" [%s]", pipex[i].infiles[in]);
				in++;
			}
			printf("]");
		}
		if (out < pipex[i].nboutfiles)
		{
			printf("\n   Tableau d'outfiles   = [");
			out = 0;
			while (pipex[i].outfiles[out])
			{
				printf(" [%s]", pipex[i].outfiles[out]);
				out++;
			}
			printf("]");
		}
		printf("\n________________________________\n\n");
		i++;
	}
}
