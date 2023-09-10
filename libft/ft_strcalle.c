/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcalle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:16:55 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/27 16:16:55 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcalle(char *str, char *c)
{
    char *str2;
    int i;
    int j;

    j = 0;
    i = 0;
    str2 = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(c) + 1));
    while (str[i])
    {
        str2[j] = str[i];
        i++;
        j++;
    }
    i = 0;
    while (c[i])
    {
        str2[j] = c[i];
        i++;
        j++;
    }
    str2[j] = '\0';
    return (str2);
}