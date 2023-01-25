/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:38:32 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 05:18:43 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(t_data *data)
{
	size_t		i;
	char		*expand;
	int			err;

	i = -1;
	if (!tab)
		return (-2);
	while (tab[++i])
	{
		err = ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			err = ft_putchar_fd(' ', 1);
		if (err == -1)
			return (-1);
	}
	return (0);
}
