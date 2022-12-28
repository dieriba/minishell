/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:38:32 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 22:34:55 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minishell.h"

int	echo(char *msg, char **env)
{
	char		**tab;
	size_t		i;
	char		*expand;
	int			err;

	i = -1;
	tab = ft_split(msg, ' ');
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
