/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:01:52 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/21 21:21:48 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_digitlen(int n)
{
	unsigned int	i;

	i = 0;
	if (n < 0)
	{
		n = -1 * n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	size = ft_digitlen(n);
	str = (char *) malloc(size * sizeof(char) + 1);
	if (str)
	{
		if (n < 0)
		{
			n = -1 * n;
			str[0] = '-';
		}
		str[size] = '\0';
		while (size-- > 0 && n > 9)
		{
			str[size] = n % 10 + '0';
			n = n / 10;
		}
		str[size] = n + '0';
	}
	return (str);
}
