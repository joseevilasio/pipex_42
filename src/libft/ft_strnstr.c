/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:04:53 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/23 14:01:13 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	index;
	size_t			i;
	size_t			x;

	i = 0;
	if (!*to_find)
		return ((char *) str);
	while (*str && i++ <= len)
	{
		if (*str == *to_find)
		{
			index = 0;
			x = i;
			while (to_find[index] && x <= len
				&& str[index] == to_find[index])
			{
				x++;
				index++;
			}
			if (index == ft_strlen(to_find))
				return ((char *) str);
		}
		str++;
	}
	return (NULL);
}
