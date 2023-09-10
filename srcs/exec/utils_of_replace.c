/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:08:42 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/02 13:08:42 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char    **double_cut(char *str)
{
    char    **new_str;
    int j;
    int i;

    i = 0;
    j = 0;
    new_str = malloc(sizeof(char *) * 3);
    new_str[j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i] && str[i] != ' ')
    {
        new_str[j][i] = str[i];
        i++;
    }
    new_str[j][i] = '\0';
    j++;
    int k = 0;
    new_str[j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (str[i])
    while (str[i])
    {
        new_str[j][k] = str[i];
        i++;
        k++;
    }
    new_str[j][k] = '\0';
    new_str[j + 1] = NULL;
    return (new_str);
}

char    *ft_replace_status(int status, char *str)
{
    int i;
    int j;

    char *str2;
    char    *num;
    j = 0;

    i = 2;
    num = ft_itoa(status);
    str2 = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(num) + 1));
    while (num[j])
    {
        str2[j] = num[j];
        j++;
    }
    while (str[i])
    {
        str2[j] = str[i];
        i++;
        j++;
    }
    str2[j] = '\0';
    free(num);
    return (str2);
}