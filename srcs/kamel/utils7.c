/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:35:34 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_count_simple_quotes(const char *str)
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

int ft_count_double_quotes(const char *str)
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

int ft_count_parentheses(const char *str)
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

int check_is_even(int num)
{
    return (num % 2 == 0);
}

char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}
