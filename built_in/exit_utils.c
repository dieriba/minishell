/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:25:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 17:17:07 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_overflow(char *num, long long res)
{
	char	*to_cmp;

	ft_malloc_less_itoa(&to_cmp, res);
	if (ft_strcmp(to_cmp, num))
		return (1);
	return (0);
}

int	check_valid_exit(char *num, long long *number)
{
	size_t	len;
	size_t	i;

	i = -1;
	len = 0;
	while (num[++i] && num[i] == '0')
		;
	if (num[i])
		len = ft_strlen(&num[i]);
	if (len > 19)
		return (-1);
	(*number) = ft_atoi(num);
	if (is_overflow(&num[i], (*number)))
		return (-1);
	return (0);
}
