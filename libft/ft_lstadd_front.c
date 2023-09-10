/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:49:46 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/23 15:49:49 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list	*begin;

	if (!alst || !*alst)
	{
		*alst = new;
		return ;
	}
	begin = *alst;
	new->next = begin;
	*alst = new;
}
