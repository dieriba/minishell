/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 06:03:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 18:42:46 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dollars(char c, char *to_clean, int i)
{
	int	valid;

	valid = 0;
	while (i > 0 && --i >= 0 && to_clean[i] > 0)
		;
	if (to_clean[i] < 0 && to_clean[i] == '\'' * -1)
		valid = -1;
	if (c == ' ' || c == 0 || valid == -1)
		return (1);
	return (valid);
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