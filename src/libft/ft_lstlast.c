/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:02:35 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/16 19:02:43 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*start;

	if (lst && lst->next)
	{
		start = lst->next;
		while (start->next)
		{
			start = start->next;
		}
		return (start);
	}
	return (lst);
}
