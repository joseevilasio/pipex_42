/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:03:28 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/16 19:03:30 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*char_ptr;

	i = 0;
	char_ptr = (unsigned char *) ptr;
	while (i < n)
	{
		char_ptr[i] = (unsigned char) c;
		i++;
	}
	return (ptr);
}
