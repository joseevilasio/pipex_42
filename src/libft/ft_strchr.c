/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:04:09 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/21 21:21:07 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	unsigned char	new_c;

	new_c = (unsigned char) c;
	while (*s)
	{
		if (*s == new_c)
			return (s);
		s++;
	}
	if (*s == new_c)
		return (s);
	return (NULL);
}
