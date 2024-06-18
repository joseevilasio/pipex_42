/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:03:14 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/16 19:03:16 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *s1, const void *s2, unsigned int n)
{
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char *) s1;
	ptr_s2 = (unsigned char *) s2;
	if (n > 0)
	{
		while (n-- > 0)
		{
			if (*ptr_s1 != *ptr_s2)
				return (*ptr_s1 - *ptr_s2);
			ptr_s1++;
			ptr_s2++;
		}
	}
	return (0);
}
