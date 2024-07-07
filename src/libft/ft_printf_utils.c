/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:59:10 by joneves-          #+#    #+#             */
/*   Updated: 2024/07/07 15:56:13 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checklen(char *str, char fmt)
{
	if (fmt == 'c' && !str)
		return (1);
	else
		return (ft_strlen(str));
}
