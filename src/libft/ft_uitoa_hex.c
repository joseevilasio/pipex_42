/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:47:59 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/07 15:56:13 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

char	*ft_uitoa_hex(unsigned int n)
{
	char	*str;
	char	*base;
	int		size;

	if (n == 0)
		return (ft_strdup("0"));
	base = "0123456789abcdef";
	size = ft_nbrlen(n);
	str = (char *) malloc((size + 1) * sizeof(char));
	if (str)
	{
		str[size] = '\0';
		while (size-- > 0)
		{
			str[size] = base[n % 16];
			n = n / 16;
		}
		return (str);
	}
	return (NULL);
}
