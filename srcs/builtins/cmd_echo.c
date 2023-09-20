/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:25:54 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 18:25:54 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char    *new_msg_echo(char *msg)
{
    char    *new;
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    if (!msg || msg == NULL)
        return (NULL);
    new = malloc(sizeof(char) * (ft_strlen(msg) + 1));
    while(msg[i])
    {
        if (msg[i] && msg[i] == '\'')
            while (msg[i] && msg[i] != '\'')
                i++;
        else if(msg[i] && msg[i] == '"')
            while (msg[i] && msg[i] != '"')
                i++;
        if (msg[i] && msg[i] == '|')
            break ;
        i++;
    }
    len = i;
    while (j < len)
    {
        new[j] = msg[j];
        i++;
        j++;
    }
    new[j] = '\0';
    // dprintf(2, "new echo : [%s]\n", new);
    return (new);
}

int count_dollars(char *str)
{
    int nb;
    int i;

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

char *change_dollard(char *str)
{
    int taille;
    int sq;
    char    *resultat;
    int i;
    int j;

    if (str == NULL)
        return (NULL);
    i = 0;
    j = 0;
    sq = 0;
    taille = ft_strlen(str);
    resultat = (char *)malloc((taille + 1 + count_dollars(str)) * sizeof(char));
    while (str[i])
    {
        if (str[i] == '\'')
        {
            resultat[j++] = str[i];
            sq++;
        }
        else if (str[i] == '$')
        {
            if (str[i + 1] && (sq % 2 == 0))
            {
                resultat[j++] = '$';
                resultat[j++] = '*';
            }
            else
                resultat[j++] = '$';
        }
        else
            resultat[j++] = str[i];
        i++;
    }
    resultat[j] = '\0';
	free(str);
    return (resultat);
}

int	cmd_echo(char *msg, int nb, int status, t_pipex *pipex)
{
	char	**new_str = NULL;
    char    *new_msg = NULL;
	int		i;

    i = 0;
    new_msg = new_msg_echo(msg);
    if (((new_msg + 7) == NULL || !(msg + 7)) && nb)
        return (free(new_msg), 1);
	else if (((new_msg + 4) == NULL || ! (new_msg + 4)) && !nb)
        return (printf("\n"), free(new_msg), 1);
	if (!nb && new_msg + 4)
        new_str = words(new_msg + 4);
	else if (nb && new_msg)
        new_str = words(new_msg + 7);
	while (new_str[i])
	{
		new_str[i] = change_dollard(new_str[i]);
		new_str[i] = replace_echo(pipex, status, new_str[i]);
		if (new_str[i + 1])
            printf("%s ", new_str[i]);
        else
            printf("%s", new_str[i]);
		i++;
	}
	if (!nb)
		printf("\n");
	free_char_double(new_str);
    free(new_msg);
	return (1);
}

char    *ft_strcpy_mall(char *src)
{
    char    *str;
    int     i;

    i = 0;
    str = malloc(sizeof(char) *(ft_strlen(src) + 1));
    while (src[i])
    {
        str[i] = src[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

void	init_cmd(t_pipex *pipex, char *commande)
{
	int	i;

	i = 0;
    if (!commande)
    {
        return ;
    }
	while (i < pipex[0].size)
	{
		pipex[i].commande = ft_strcpy_mall(commande);
		i++;
	}
}
