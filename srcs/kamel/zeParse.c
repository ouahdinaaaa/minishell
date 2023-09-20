/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zeParse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:35:38 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int isstartingwith(char *base, char *start)
{
    size_t i;

    i = 0;
    while (i < ft_strlen(start))
    {
        if (base[i] != start[i])
            return (0);
        i++;
    }
    return (1);
}

int countchevronsq(char *str)
{
    int nb;
    int i;
    int dq;
    int sq;

    i = 0;
    nb = 0;
    dq = 0;
    sq = 0;
    while (str[i])
    {
        if (str[i] == '"')
        {
            if (sq % 2 == 0)
                dq++;
        }
        else if (str[i] == '\'')
        {
            if (dq % 2 == 0)
                sq++;
        }
        else if (str[i] == '>' || str[i] == '<')
        {
            if (dq % 2 == 1 || sq % 2 == 1)
                nb++;
        }
        i++;
    }
    return (nb);
}

int *kamindexchev(char *str)
{
    size_t i;
    int w;
    int *tab;
    size_t t;
    int *indexchev;
    int j;

    j = 0;
    indexchev = malloc(sizeof(int) * countchevronsq(str));
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
        if (str[i] == '>' || str[i] == '<')                  // Si je tombe sur un chevron
        {
            if (tab[1] == 1 || tab[2] == 1)
                indexchev[j++] = w;
        }
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
    return (free(tab), indexchev);
}

int checkifindexchevron(int index, int *tab, int taille)
{
    int i;

    i = 0;
    while (i < taille)
    {
        if (index == tab[i] - 1)
        {
            return (1);
        }
        i++;
    }
    return (0);
}

void    putquoteschevrons(char **words, int nbmots, int *indextab, int nbindex)
{
    int i;

    i = 0;
    while (i < nbmots)
    {
        if (checkifindexchevron(i, indextab, nbindex))
            words[i] = strjoinExtremites(words[i], '\'');
        i++;
    }
    free(indextab);
}

char **decoupage(char *str)
{
    char    **words;

    words = quotes(str);
    putquoteschevrons(words, ft_countwords(str), kamindexchev(str), countchevronsq(str));
    if (str)
        free(str);
    return (words);
}

int    conditionsquotesimpaires(char **p, int ip)
{
    return (check_is_even(ft_count_simple_quotes(p[ip])) == 0
			|| check_is_even(ft_count_double_quotes(p[ip])) == 0
			|| ft_count_parentheses(p[ip]) != 0);
}

void    quotesimpaires(char **p, t_pipex *pipex, int ip)
{
    printf("\nError : Nombre de quotes ou parentheses impair");
	pipex[ip].erreur = 0;
    free_char_double(p);
}

char* concatwithspace(char* str1, char* str2)
{
    size_t len1 = (str1 != NULL) ? strlen(str1) : 0;
    size_t len2 = (str2 != NULL) ? strlen(str2) : 0;
    size_t totalLen = len1 + len2 + 2;

    char* result = (char*)malloc(totalLen);

    if (result != NULL)
    {
        if (len1 > 0)
        {
            ft_strcpy(result, str1);
            if (len2 > 0)
            {
                ft_strcat(result, " ");
                ft_strcat(result, str2);
            }
        }
        else if (len2 > 0)
            ft_strcpy(result, str2);
    }
    if (str1)
        free(str1);
    return (result);
}

int ft_count_files(char c, char *str)
{
    int nb;
    int i;

    i = 0;
    nb = 0;
    while(str[i])
    {
        if (str[i] == c)
            nb++;
        i++;
    }
    return (nb);
}
