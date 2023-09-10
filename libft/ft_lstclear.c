/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:50:37 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/23 16:25:52 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*begin;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		begin = (*lst)->next;
		ft_lstdelone((*lst), del);
		(*lst) = begin;
	}
}
