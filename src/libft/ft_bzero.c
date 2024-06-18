/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:00:20 by joneves-          #+#    #+#             */
/*   Updated: 2024/04/16 19:00:24 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_bzero(void *ptr, unsigned int n)
{
	unsigned int	i;
	unsigned char	*char_ptr;

	i = 0;
	char_ptr = ptr;
	while (i < n)
	{
		char_ptr[i] = (unsigned char) 0;
		i++;
	}
}
