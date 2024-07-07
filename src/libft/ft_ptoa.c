/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:15:20 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/07 15:56:13 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(unsigned long n)
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

char	*ft_ptoa(unsigned long n)
{
	char	*str;
	char	*base;
	int		size;

	if (!n || n == 0)
		return (ft_strdup("(nil)"));
	base = "0123456789abcdef";
	size = ft_nbrlen(n);
	str = (char *) malloc((size + 3) * sizeof(char));
	if (str)
	{
		str[size + 2] = '\0';
		while (size-- > 0)
		{
			str[size + 2] = base[n % 16];
			n = n / 16;
		}
		str[0] = '0';
		str[1] = 'x';
		return (str);
	}
	return (NULL);
}
