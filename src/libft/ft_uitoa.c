/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:01:52 by joneves-          #+#    #+#             */
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
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		size;

	if (n == 0)
		return (ft_strdup("0"));
	size = ft_nbrlen(n);
	str = (char *) malloc((size + 1) * sizeof(char));
	if (str)
	{
		str[size] = '\0';
		while (size-- > 0 && n > 9)
		{
			str[size] = n % 10 + '0';
			n = n / 10;
		}
		str[size] = n + '0';
		return (str);
	}
	return (NULL);
}
