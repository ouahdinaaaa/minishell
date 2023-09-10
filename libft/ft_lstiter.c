/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:51:53 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/23 15:51:57 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*begin;

	if (!lst)
		return ;
	begin = lst;
	while (begin)
	{
		(*f)(begin->content);
		begin = begin->next;
	}
}
