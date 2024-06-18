/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:04:57 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/22 18:54:33 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	size_t			i;
	unsigned char	new_c;

	new_c = (unsigned char) c;
	i = ft_strlen(s) + 1;
	while (i-- > 0)
	{
		if (s[i] == new_c)
			return (s + i);
	}
	return (NULL);
}
