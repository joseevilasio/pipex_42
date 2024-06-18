/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:02:01 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/21 21:21:45 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_)
{
	t_list	*start;

	if (*lst)
	{
		start = *lst;
		while (start->next)
			start = start->next;
		start->next = new_;
	}
	else
		*lst = new_;
}
