/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/07/13 18:17:08 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int countSingleQuotes(const char *str)
{
	int i;
    int count;

    if (str == NULL)
    {
        return (0);
    }
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
                i++;
        }
        else if (str[i] && str[i] == '\'')
        {
            count++;
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (str[i] && str[i] == '\'')
                count++;
        }
        i++;
    }
    return (count);
}

int countDoubleQuotes(const char *str)
{
	int i;
    int count;

    if (str == NULL)
    {
        return (0);
    }
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
        }
        else if (str[i] && str[i] == '"')
        {
            count++;
            i++;
            while (str[i] && str[i] != '"')
                i++;
            if (str[i] && str[i] == '"')
                count++;
        }
        i++;
    }
    return (count);
}

int countParentheses(const char *str)
{
    int i;
    int countouverture;
    int countfermeture;

    if (str == NULL)
    {
        return (0);
    }
    countouverture = 0;
    countfermeture = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '(')
            countouverture++;
        else if (str[i] == ')')
            countfermeture++;
        else if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
                i++;
        }
        else if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
        }
        i++;
    }
    return (countouverture - countfermeture);
    
}

int isEven(int num)
{
    return (num % 2 == 0);
}
