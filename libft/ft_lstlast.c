/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbouzegh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:17 by kbouzegh          #+#    #+#             */
/*   Updated: 2022/11/23 15:52:28 by kbouzegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*begin;

	begin = lst;
	while (begin != NULL && begin->next != NULL)
		begin = begin->next;
	return (begin);
}
