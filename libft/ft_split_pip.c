/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:08:22 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/14 13:08:22 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int count_words_pip(const char *str, char c)
{
    int i;
    int j;
    int quotes = 0;

    i = 0;
    j = 0;
    while (*str)
    {
        if (*str == '"')
            quotes = !quotes;
        if (*str != c || (quotes && *str == '"'))
        {
            if (j == 0)
            {
                j = 1;
                i++;
            }
        }
        else
            j = 0;
        str++;
    }
    return (i);
}
char *word_dup_pip(const char *str, int start, int finish)
{
    char *word;
    int i;

    i = 0;
    word = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (start <= finish)
    {
        if (str[start] != '"')
        {
            word[i] = str[start];
            i++;
        }
        start++;
    }
    word[i] = '\0';
    return (word);
}

char **ft_split_pip(char const *s, char c)
{
    size_t i;
    size_t j;
    int index;
    char **split;
    int quote;
    int end;
    int start;

    split = (char **)malloc((count_words_pip(s, c) + 1) * sizeof(char *));
    if (!s || !split)
        return (NULL);
    i = 0;
    j = 0;
    index = -1;
    quote = 0;
    while (s[i])
    {
        if (s[i] == '"')
            quote = !quote;
        else if (s[i] != c || quote)
        {
            if (index < 0)
                index = i;
        }
        else if (index >= 0)
        {
            start = index;
            end = i - 1;
            split[j] = word_dup_pip(s, start, end);
            j++;
            index = -1;
        }
        i++;
    }
    if (index >= 0)
    {
        split[j] = word_dup_pip(s, index, i - 1);
        j++;
    }
    split[j] = NULL;
    return (split);
}

// int main(int argc, char **argv) 
// {
//     if (argc != 2)
//         return (1);
//     char **result = ft_split_pip(argv[1], ' ');
//     int i = 0;
//     while(result[i]) 
//     {
//         printf("[%s]\n", result[i]);
//         free(result[i]);
//         i++;
//     }
//     free(result);
//     return (0);
// }
