/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:04:24 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/23 12:40:53 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	size;
	unsigned int	size_s1;
	unsigned int	size_s2;

	if (s1 && s2)
	{
		size_s1 = ft_strlen((char *) s1);
		size_s2 = ft_strlen((char *) s2);
		size = size_s1 + size_s2;
		str = (char *) malloc(size * sizeof(char) + 1);
		if (str)
		{
			ft_strlcpy(str, (char *)s1, size_s1 + 1);
			ft_strlcpy(str + size_s1, (char *)s2, size_s2 + 1);
			return (str);
		}
	}
	return (NULL);
}
