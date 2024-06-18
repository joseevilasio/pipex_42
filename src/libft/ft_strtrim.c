/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:05:02 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/23 12:42:37 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_strspn(char const *s1, char const *set)
{
	unsigned int	len;

	len = 0;
	while (*s1 && ft_strchr((char *) set, *s1))
	{
		len++;
		s1++;
	}
	return (len);
}

static unsigned int	ft_strrspn(char const *s1, char const *set)
{
	unsigned int	len;
	unsigned int	size;

	len = 0;
	if (ft_strlen((char *) s1) == 0)
		size = 0;
	else
		size = ft_strlen((char *) s1) - 1;
	while (s1[size] && ft_strchr((char *) set, s1[size]))
	{
		len++;
		size--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	start;
	unsigned int	end;
	unsigned int	size;

	if (s1 && set)
	{
		start = ft_strspn(s1, set);
		if (start == (unsigned int) ft_strlen((char *) s1))
			return (ft_strdup(""));
		end = ft_strrspn(s1, set);
		size = ft_strlen((char *) s1) - (start + end);
		str = (char *) malloc(size * sizeof(char) + 1);
		if (str)
		{
			ft_strlcpy(str, (char *) s1 + start, size + 1);
			return (str);
		}
	}
	return (NULL);
}
