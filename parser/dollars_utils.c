/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 06:03:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/09 01:48:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dollars(char c)
{
	if (c == ' ' || c == 0)
		return (1);
	return (0);
}

char	*is_shell_variable(t_data *data, char *line)
{
	char	*res;

	res = NULL;
	if (ft_strcmp(line, "?") == 0)
		ft_malloc_less_itoa(&res, data -> status);
	else if (ft_strcmp(line, "$") == 0)
		return ("cantGetPid");
	return (res);
}
