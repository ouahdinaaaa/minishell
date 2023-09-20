/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqdq-utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <kbouzegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:33:07 by kbouzegh          #+#    #+#             */
/*   Updated: 2023/09/18 16:34:55 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    init_tab_ping_dollars(int *tab, int zero)
{
    tab[0] = zero;
    tab[1] = 0;
    tab[2] = 0;
    tab[3] = 0;
}

// tab[0] taille
// tab[1] sq
// tab[2] i
// tab[3] j

char	*convertirDollarEnEuro(char *str)
{
	char	*resultat;
    int     tab[4];

    tab[0] = ft_strlen(str);
    tab[1] = 0;
    tab[2] = 0;
    tab[3] = 0;
	if (str == NULL)
		return (NULL);
	resultat = (char *)malloc((size_t)tab[0] + 1 + (size_t)ft_count_dollars(str));
	while (str[tab[2]])
	{
		if (str[tab[2]] == '\'')
		{
			resultat[tab[3]++] = str[tab[2]];
			tab[1]++;
		}
		else if (str[tab[2]] == '$')
		{
			if (str[tab[2] + 1] && (tab[1] % 2 == 0))
			{
				resultat[tab[3]++] = '$';
				resultat[tab[3]++] = '*';
			}
			else
				resultat[tab[3]++] = '$';
		}
		else
			resultat[tab[3]++] = str[tab[2]];
		tab[2]++;
	}
	resultat[tab[3]] = '\0';
	return (resultat);
}

void	remplirTableauDeZeros(int *tableau, int taille)
{
	int	i;

	i = 0;
	while (i < taille)
	{
		tableau[i] = 0;
		i++;
	}
}

int	isThereChar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	swapPointers(char *ptr1, char *ptr2)
{
	char	*temp;

	temp = ptr1;
	ptr1 = ptr2;
	ptr2 = temp;
}
