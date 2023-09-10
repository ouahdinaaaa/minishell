/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/13 18:17:08 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int nombremots(char *str)
{
    int mot;
    int i;
    char c;
    int dq;

    dq = 0;
    i = 0;
    mot = 0;
    c = ' ';
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        while (str[i] && str[i] == '"')
        {
            i++;
            dq++;
        }
        if (dq % 2 == 1)
        {
            if (c == ' ')
                mot++;
            while (str[i] && str[i] != '"')
                i++;
            dq++;
            i++;
        }
        while (str[i] && str[i] == '"')
        {
            dq++;
            i++;
        }
        if (dq % 2 == 0)
        {
            c = str[i];
            while (str[i] && str[i] == ' ')
                i++;
            while (str[i] && str[i] != '"')
            {
                if (str[i] == ' ')
                    mot++;
                i++;
            }
        }
    }
    return (mot + 1);
}

char    **write_mots(char *str, int nb)
{
    char **strs;
    char c;
    int i;
    int j;
    int dq;
    
    i = 0;
    j = 0;
    dq = 0;
    c = ' ';
    strs = malloc(sizeof(char *) * (nb + 1));
    while (str[i] && str[i] == ' ')
        i++;
    int k = 0;
    while (str[i])
    {
        while (str[i] && str[i] == '"')
        {
            i++;
            dq++;
        }
        if (dq % 2 == 1)
        {
            if (c == ' ')
                strs[j] = malloc(sizeof(char) * 100);
            k = 0;
            while (str[i] && str[i] != '"')
            {
                strs[j][k] = str[i];
                i++;
                k++;
            }
            dq++;
            i++;
        }
        while (str[i] && str[i] == '"')
        {
            dq++;
            i++;
        }
        if (dq % 2 == 0)
        {
            c = str[i];
            while (str[i] && str[i] == ' ')
                i++;
            while (str[i] && str[i] != '"')
            {
                if (c == ' ')
                {
                    while (str[i] && str[i] == ' ')
                        i++;
                    strs[j][k] = '\0';
                    j++;
                    k = 0;
                    strs[j] = malloc(sizeof(char) * 100);
                    while (str[i] && str[i] != ' ' && str[i] != '"')
                    {
                        strs[j][k] = str[i];
                        i++;
                        k++;
                    }
                }
                else if (str[i] && str[i] != ' ')
                {
                    while (str[i] && str[i] != ' ' && str[i] != '"')
                    {
                        strs[j][k] = str[i];
                        i++;
                        k++;
                    }
                }
            }
            i++;
            }
    }
    strs[j + 1] = NULL;
    return (strs);
}


int detectSpace(const char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ') 
            return (1);
        i++;
    }
    return (0);
}

void putDoubleQuote(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        if (detectSpace(str[i]))
        {
            int originalLength = strlen(str[i]);
            int newLength = originalLength + 2;
            char *newStr = (char *)malloc(newLength + 1);

            if (newStr != NULL)
            {
                newStr[0] = '"';
                strcpy(newStr + 1, str[i]);
                newStr[newLength - 1] = '"';
                newStr[newLength] = '\0';

                free(str[i]);
                str[i] = newStr;
            }
        }
        i++;
    }
}

// int main()
// {
//     char *words[] = 
//     {
//         "hello",
//         "world with space",
//         "test",
//         "multiple words here"
//     };
//     putDoubleQuote(words);
//     for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
//         printf("%s\n", words[i]);
//         free(words[i]); // Libère la mémoire allouée pour chaque chaîne
//     }
//     return 0;
// }


// Main pour tester WRITEMOTS & NOMBREMOTS & PUTDOUBLEQUOTES

// int main()
// {
//     char *strs = "\" ayakamel  \" et moi okkk \"marche\"";
//     int i;
//     i = 0;
//     char **res;
//     printf("\n%s\n", strs);
//     printf("\n%d\n", nombremots(strs));
//     res = write_mots(strs, 5);
//     putDoubleQuote(res);
//     while (res[i])
//     {
//         printf("res : %s\n", res[i]);
//         i++;
//     }
//     return (0);
// }
