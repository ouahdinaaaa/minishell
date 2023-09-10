/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:25:54 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/06/20 18:25:54 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	cmd_echo(char *msg, int nb)
{
	char	**str;
	int		i;

	i = 0;
	if (msg)
		str = ft_split_pip(msg, ' ');
	while(str[i] && str[i + 1])
	{
		if (i == 0)
			printf("🗣️ %s ", str[i]);
		else
			printf("%s ", str[i]);
		i++;
	}
	if (!nb)
		printf("%s\n", str[i]);
	else
		printf("%s", str[i]);
	free_char_double(str);
	return (1);
}