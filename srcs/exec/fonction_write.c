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

char	*add_write_str(char *str1, char *str2, char *str3, char *str4)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)
				+ ft_strlen(str3) + ft_strlen(str4) + 1));
	if (str1)
	{
		while (str1[i])
		{
			dest[j] = str1[i];
			i++;
			j++;
		}
	}
	i = 0;
	if (str2)
	{
		while (str2[i])
		{
			dest[j] = str2[i];
			i++;
			j++;
		}
	}
	add2write(dest, str3, str4, j);
	return (dest);
}

char	*add2write(char *dest, char *str3, char *str4, int j)
{
	int	i;

	i = 0;
	if (str3)
	{
		while (str3[i])
		{
			dest[j] = str3[i];
			i++;
			j++;
		}
	}
	i = 0;
	if (str4)
	{
		while (str4[i])
		{
			dest[j] = str4[i];
			i++;
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

void	end_function_str_path(char **new_str, t_pipex *pipex, char *str)
{
	free_char_double(new_str);
	free(pipex->str_path);
	pipex->str_path = malloc(sizeof(char) * (ft_strlen(str) + 1));
	pipex->str_path = ft_strcpy(pipex->str_path, str);
	free(str);
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
