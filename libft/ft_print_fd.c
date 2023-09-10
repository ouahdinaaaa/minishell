/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:57:51 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/11 16:57:51 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_print_fd(char *s1, char *s2, char *s3, char *s4)
{
    char *str1;
    char *str2;

    str1 = NULL;
    str2 = NULL;
    if (s2)
    {
        str1 = ft_strjoin(s1, " ");
        str2 = ft_strjoin(str1, s2);
        free(str1);
    }
    if (s3)
    {
        str1 = ft_strjoin(str2, " ");
        free(str2);
        str2 = ft_strjoin(str1, s3);
        free(str1);
    }
    if (s4)
    {
        str1 = ft_strjoin(str2, " ");
        free(str2);
        str2 = ft_strjoin(str1, s4);
        free(str1);
    }
    ft_putstr_fd(str2, 2);
    free(str2);
}