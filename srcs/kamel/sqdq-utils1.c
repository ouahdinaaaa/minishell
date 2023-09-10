/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/13 18:17:08 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int countDollars(char *str)
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

char *convertirDollarEnEuro(char *str)
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
    resultat = (char *)malloc((taille + 1 + countDollars(str)) * sizeof(char));
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
    return (resultat);
}

void remplirTableauDeZeros(int *tableau, int taille)
{
    int i;

    i = 0;    
    while (i < taille)
    {
        tableau[i] = 0;
        i++;
    }
}

int isThereChar(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
            return (1);
        }
        i++;
    }
    return (0);
}

char *ft_strcat(char *dest, const char *src)
{
    char *temp;
    
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
