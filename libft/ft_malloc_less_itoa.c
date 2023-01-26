/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_less_itoa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:34:52 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 21:56:50 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = (n < 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void ft_malloc_less_itoa(char **res, int n)
{
	int				i;
	int				j;
	unsigned int	nb;
	static char		str[11] = {0};

	nb = -(n < 0) * (n) + (n > 0) * (n);
	i = (n < 0);
	j = ft_nblen(n);
	if (n < 0)
		str[0] = '-';
	str[j] = 0;
	while (--j >= i)
	{
		str[j] = (nb % 10) + '0';
		nb /= 10;
	}
	(*res) = str;
}
