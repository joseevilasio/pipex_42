/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:20:03 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/23 12:36:39 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	char			*ptrs;
	unsigned int	len_s;
	unsigned int	size;

	if (s)
	{
		len_s = ft_strlen((char *)s);
		size = len_s - start;
		if (len_s <= start)
		{
			len = 0;
			start = len_s;
		}
		if (len > size)
			len = size;
		str = (char *) malloc(len * sizeof(char) + 1);
		if (str)
		{
			ptrs = (char *) s + start;
			ft_strlcpy(str, ptrs, len + 1);
			return (str);
		}
	}
	return (NULL);
}
