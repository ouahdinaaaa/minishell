/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqdq.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/06 17:21:30 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int countWords(char *str)
{
    size_t i;
    int w;
    int *tab;
    size_t t;

    // tab[0] mot
    // tab[1] sq
    // tab[2] dq

    //      "mot"" "  mot" "mot

    if (str == NULL)
        return (0);
    i = 0;
    w = 0;
    t = ft_strlen(str);
    tab = malloc(sizeof(int) * 3);
    remplirTableauDeZeros(tab, 3);
    while (str[i] && i < t)
    {
        while (str[i] && (str[i] == ' ') && tab[0] == 0 && i < t)
            i++;
        if (str[i] == '"')                  // Si je tombe sur une DQ
        {
            if (tab[1] == 0)                // Si je ne suis pas entre deux SQ
            {
                if (tab[2] == 1)            // Si une DQ a deja ete ouverte
                {
                    tab[2] = 0;
                    if (str[i + 1] && str[i + 1] == ' ')
                        tab[0] = 0;
                }
                else                        // Si aucune DQ n a ete ouverte
                {
                    tab[2] = 1;
                    if (tab[0] == 0)        // Si je ne suis pas dans un mot
                    {
                        tab[0] = 1;
                        w++;
                    }
                }
            }
            i++;
        }
        else if (str[i] == '\'')
        {
            if (tab[2] == 0)                // Si je ne suis pas entre deux DQ
            {
                if (tab[1] == 1)            // Si une SQ a deja ete ouverte
                {
                    tab[1] = 0;
                    if (str[i + 1] && str[i + 1] == ' ')
                        tab[0] = 0;
                }
                else                        // Si aucune SQ n a ete ouverte
                {
                    tab[1] = 1;
                    if (tab[0] == 0)        // Si je ne suis pas dans un mot
                    {
                        tab[0] = 1;
                        w++;
                    }
                }
            }
            i++;
        }
        else
        {
            if (str[i] == ' ' && tab[1] == 0 && tab[2] == 0 && tab[0] == 1)
                tab[0] = 0;
            else if (str[i] != ' ' && tab[1] == 0 && tab[2] == 0 && tab[0] == 0 && i < t)
            {
                w++;
                tab[0] = 1;
            }
            i++;
        }
    }
    free (tab);
    return (w);
}

int *allocWords(char *str)
{
    int i;
    int w;
    int *alloc;
    int *tab;

    i = 0;
    w = 0;
    alloc = malloc(sizeof(int) * countWords(str));
    remplirTableauDeZeros(alloc, countWords(str));
    tab = malloc(sizeof(int) * 4);
    remplirTableauDeZeros(tab, 4);
    while (str[i])
    {
        while (str[i] && (str[i] == ' ') && tab[3] == 0)
            i++;
        if (str[i] && (str[i] == '"'))
        {
            if (tab[1] == 1)
            {
                alloc[w - 1]++;
                i++;
            }
            else if (str[i + 1] && str[i + 1] == '"' && tab[3] == 0)
                i = i + 2;
            else if (tab[3] == 0)
            {
                i++;
                w++;
                tab[0] = 1;
                tab[3] = 1;
            }
            else
            {
                if (tab[0] == 1)
                {
                    tab[0] = 0;
                    if (str[i + 1] == ' ')
                        tab[3] = 0;
                }
                else if (tab[0] == 0)
                    tab[0] = 1;
                i++;
            }
        }
        else if (str[i] && (str[i] == '\''))
        {
            if (tab[0] == 1)
            {
                alloc[w - 1]++;
                i++;
            }
            else if (str[i + 1] && str[i + 1] == '\'' && tab[3] == 0)
                i = i + 2;
            else if (tab[3] == 0)
            {
                i++;
                w++;
                tab[1] = 1;
                tab[3] = 1;
            }
            else
            {
                if (tab[1] == 1)
                {
                    tab[1] = 0;
                    if (str[i + 1] == ' ')
                        tab[3] = 0;
                }
                else if (tab[1] == 0)
                    tab[1] = 1;
                i++;
            }
        }
        else if (str[i] != ' ')
        {
            if (tab[3] == 0)
            {
                w++;
                alloc[w - 1]++;
                i++;
                tab[3] = 1;
            }
            else
            {
                alloc[w - 1]++;
                i++;
            }
        }
        else if (str[i] && str[i] == ' ')
        {
            if (tab[1] == 0 && tab[0] == 0)
            {
                i++;
                tab[3] = 0;
            }
            else
            {
                alloc[w - 1]++;
                i++;
            }
        }
    }
    return (alloc);
}

char **words(char *str)
{
    int i;
    int w;
    int j;
    char **words;
    int *tab;
    int *alloc;

    i = 0;
    j = 0;
    w = 0;
    alloc = allocWords(str);
    words = malloc(sizeof(char *) * countWords(str));
    while (i < countWords(str))
    {
        words[i] = malloc(sizeof(char) * alloc[i] + 1);
        i++;
    }
    i = 0;
    remplirTableauDeZeros(alloc, countWords(str));
    tab = malloc(sizeof(int) * 4);
    remplirTableauDeZeros(tab, 4);
    while (str[i])
    {
        while (str[i] && (str[i] == ' ') && tab[3] == 0)
            i++;
        if (str[i] && str[i] != '\0' && (str[i] == '"'))
        {
            if (tab[1] == 1)
            {
                words[w - 1][j] = str[i];
                j++;
                i++;
            }
            else if (str[i + 1] && str[i + 1] == '"' && tab[3] == 0)
                i = i + 2;
            else if (tab[3] == 0)
            {
                i++;
                w++;
                j = 0;
                tab[0] = 1;
                tab[3] = 1;
            }
            else
            {
                if (tab[0] == 1)
                {
                    tab[0] = 0;
                    if (str[i + 1] == ' ')
                    {
                        tab[3] = 0;
                        words[w - 1][j] = '\0';
                    }
                }
                else if (tab[0] == 0)
                    tab[0] = 1;
                i++;
            }
        }
        else if (str[i] && str[i] != '\0' && (str[i] == '\''))
        {
            if (tab[0] == 1)
            {
                words[w - 1][j] = str[i];
                j++;
                i++;
            }
            else if (str[i + 1] && str[i + 1] == '\'' && tab[3] == 0)
                i = i + 2;
            else if (tab[3] == 0)
            {
                i++;
                w++;
                j = 0;
                tab[1] = 1;
                tab[3] = 1;
            }
            else
            {
                if (tab[1] == 1)
                {
                    tab[1] = 0;
                    if (str[i + 1] == ' ')
                    {
                        tab[3] = 0;
                        words[w - 1][j] = '\0';
                    }
                }
                else if (tab[1] == 0)
                    tab[1] = 1;
                i++;
            }
        }
        else if (str[i] && str[i] != '\0' && str[i] != ' ')
        {
            if (tab[3] == 0)
            {
                w++;
                j = 0;
                words[w - 1][j] = str[i];
                j++;
                i++;
                tab[3] = 1;
            }
            else
            {
                words[w - 1][j] = str[i];
                j++;
                i++;
            }
        }
        else if (str[i] && ((str[i] != '\0' && str[i] == ' ') || !str[i + 1]))
        {
            if (tab[1] == 0 && tab[0] == 0)
            {
                i++;
                tab[3] = 0;
                words[w - 1][j] = '\0';
            }
            else
            {
                words[w - 1][j] = str[i];
                j++;
                i++;
            }
        }
    }
    words[w - 1][j] = '\0';
    words[w] = NULL;
    free (alloc);
    free (tab);
    int k = 0;
    while (words[k])
    {
        k++;
    }
    return (words);
}
