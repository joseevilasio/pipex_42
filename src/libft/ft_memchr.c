/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:03:09 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/21 21:21:24 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	char_s;

	str = (unsigned char *) s;
	char_s = (unsigned char) c;
	if (n > 0)
	{
		while (n-- > 0)
		{
			if (*str == char_s)
				return (str);
			str++;
		}
	}
	return ((void *) 0);
}
