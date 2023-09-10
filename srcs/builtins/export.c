/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:38:28 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/08/17 23:38:28 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char    **add_export(char **env_cpy) 
{
    int i;
    char    *str1;
    int     new_len;
    char    *new_str;
    char    **new_env;

    i = 0;
    new_len = 0;
    str1 = NULL;
    new_env = malloc(sizeof(char *) * (size_of_env(env_cpy) + 1));
    while (env_cpy[i]) 
    {
        str1 = malloc(sizeof(char) * ft_strlen(env_cpy[i]) + 1);
        str1  = ft_strcpy(str1, env_cpy[i]);
        new_len = ft_strlen(str1) + strlen("export ") + 1;
        new_str = malloc(sizeof(char) * (new_len) + 1);
        if (new_str) 
        {
            new_str = ft_strcpy(new_str, "export ");
            new_env[i] = ft_strjoin(new_str, str1);   
            free(new_str); 
            free(str1);
        }
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

char    *copy1(char  *str)
{
    int i = 0;
    char    *res = NULL;

    while (str[i])
    {
        if (str[i] == '=')
            break ;
        i++;
    }
    i++;
    res = malloc(sizeof(char) * (i + 2));
    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            res[i] = str[i];
            res[i + 1] = '"';
            i++;
            break ;
        }
        res[i] = str[i];
        i++;
    }
    res[i + 1] = '\0';
    return (res);
}

char    *copy2(char *str)
{

    char    *str2 = NULL;
    int     i = 0;
    int     len = 0;
    int     j = 0;

    while (str[i] && str[i] != '=')
        i++;
    j = i + 1;
    while (str[i])
    {
        i++;
        len++;
    }
    str2 = malloc(sizeof(char) * (len + 2));
    i = 0;
    while (str[j])
    {
        str2[i] = str[j];
        i++;
        j++;
    }
    str2[i] = '"';
    str2[i + 1] = '\0';
    return (str2);
}

char    **replace_export(char **env, int i)
{
    char    *str1 = NULL;
    char    *str2 = NULL;
    char    **new_str;
    char    *join;

    new_str = malloc(sizeof(char *) * (size_of_env(env) + 100));
    while (env[i])
    {
        str1 = copy1(env[i]);
        str2 = copy2(env[i]);
        new_str[i] = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
        if (new_str[i])
        {
            join = ft_strjoin(str1, str2);
            if (join)
            {
                new_str[i] = ft_strcpy(new_str[i], join);
                free(join);
            }
            free(str1);
            free(str2);
        }
        i++;
    }
    new_str[i] = NULL;
    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
    return (new_str);
}

void    swap_infinie(char **str1, char **str2) 
{
    char *tmp;
    
    tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

void    sort_env(char ***env, int size, int index) 
{
    int j;

    if (index >= size - 1) 
            return;
    j = 0;
    while (j < size - index - 1) 
    {
        if (strcmp((*env)[j], (*env)[j + 1]) > 0) 
            swap_infinie(&(*env)[j], &(*env)[j + 1]);
        j++;
    }
    sort_env(env, size, index + 1);
}

void    sort_new_env(char ***env, int size, int index)
{
    int j;

    if (index >= size - 1) 
            return;
    j = 0;
    while (j < size - index - 1) 
    {
        if (strcmp((*env)[j], (*env)[j + 1]) > 0) 
            swap_infinie(&(*env)[j], &(*env)[j + 1]);
        j++;
    }
    sort_new_env(env, size, index + 1);
}


char    **export_fake_env(char **env)
{
    char    **env_copy;

    env_copy = add_export(env);
    env_copy = replace_export(env_copy, 0);
    sort_env(&env_copy, size_of_env(env_copy), 0);
    return (env_copy);
}

void	init_fake_env(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	while (i < pipex[0].size)
	{
		pipex[i].fake_env = ft_strcpy_double(env);
		i++;
	}
}