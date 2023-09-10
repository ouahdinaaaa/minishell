/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:48:44 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/10 01:48:44 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char    *add_write_str(char *str1, char *str2, char *str3, char *str4)
{
    char    *dest;
    int i;
    int j;

    i = 0;
    j = 0;
    dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + ft_strlen(str4) + 1));
    while (str1[i])
    {
        dest[j] = str1[i];
        i++;
        j++;
    }
    i = 0;
    while (str2[i])
    {
        dest[j] = str2[i];
        i++;
        j++;
    }
    i = 0;
    while (str3[i])
    {
        dest[j] = str3[i];
        i++;
        j++;
    }
    i = 0;
    while (str4[i])
    {
        dest[j] = str4[i];
        i++;
        j++;
    }
    dest[j] = '\0';
    return (dest);
}

// int main(void)
// {
//     char *str = "🤡 \033[38;5;166m [";
//     char *str2 = "and you noew";
//     char *str3 = "Command not found 🤡";
//     char *dest;

//     dest = add_write_str(str, str2, str3, "");
//     printf("dest : [%s]\n", dest);
//     free(dest);
// }