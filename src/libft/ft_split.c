/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:03:54 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/23 12:46:11 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ischar(char *s, char c)
{
	if (s == NULL)
		return (s);
	while (*s == c)
		s++;
	return (s);
}

static unsigned int	ft_countslices(char *s, char c)
{
	unsigned int	i;

	i = 1;
	if (s == NULL || *s == '\0')
		return (0);
	if (ft_strlen((char *)s) == 0 && !*s)
		return (0);
	s = ft_ischar(s, c);
	while (*s)
	{
		if (*s == c)
		{
			s = ft_ischar(s, c);
			if (*s != '\0')
				i++;
			else
				s--;
		}
		s++;
	}
	return (i);
}

static void	ft_free(char **slices, int i)
{
	while (i > 0)
		free(slices[--i]);
	free(slices);
}

static char	*ft_sliced(char *s, char c)
{
	char			*sliced;
	char			*swap;
	unsigned int	size;

	s = ft_ischar((char *) s, c);
	swap = (char *) s;
	swap = ft_strchr((char *) s, c);
	if (swap == NULL)
		size = ft_strlen((char *) s);
	else
		size = ft_strlen((char *) s) - ft_strlen(swap);
	sliced = (char *) malloc(size * sizeof(char) + 1);
	if (sliced)
	{
		ft_strlcpy(sliced, (char *) s, size + 1);
		return (sliced);
	}
	free(sliced);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**slices;
	int		slices_size;
	int		i;

	slices_size = ft_countslices((char *) s, c);
	slices = (char **) malloc((slices_size + 1) * sizeof(char *));
	i = 0;
	if (slices)
	{
		while (slices_size-- > 0 && *s)
		{
			slices[i] = ft_sliced((char *) s, c);
			if (!slices[i])
			{
				ft_free(slices, i);
				return (NULL);
			}
			s = ft_ischar((char *) s, c) + ft_strlen(slices[i]);
			i++;
		}
		slices[i] = NULL;
		return (slices);
	}
	return (NULL);
}
