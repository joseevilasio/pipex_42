/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:01:01 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/21 21:21:52 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*elem;

	elem = (void *) malloc((nelem * elsize) * sizeof(unsigned char));
	if (elem)
	{
		ft_memset(elem, 0, (nelem * elsize));
		return (elem);
	}
	return (NULL);
}
