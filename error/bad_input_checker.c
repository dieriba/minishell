/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:13:47 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 00:23:18 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_in_front(char *to_parse, int token, size_t *j)
{
	int		flags;
	size_t	i;

	i = *j;
	flags = -1;
	while (to_parse[++i] && ft_strchr(DELIM_TOKEN_SP, to_parse[i]))
		;
	while (to_parse[i] && ft_isspace(to_parse[i]))
		i++;
	if (to_parse[i] && ft_strchr(BASE_STOP, token)
		&& !ft_strchr(BASE_STOP, to_parse[i]))
		flags = 1;
	else if (to_parse[i] && ft_strchr(R_COMBO, token)
		&& !ft_strchr(DELIM_TOKEN_SP, to_parse[i]))
		flags = 1;
	*j = i;
	return (flags);
}

int	valid_double(char *to_parse, size_t i)
{
	if (to_parse[i] != '"')
		return (0);
	if (i > 0 && to_parse[i - 1] == '\\')
		return (0);
	return (1);
}

int	check_function(char *to_parse, size_t i)
{
	int	err;

	err = 0;
	if (to_parse[i] == '(' || to_parse[i] == ')')
		return (0);
	if (to_parse[i] == R_IN && to_parse[i + 1] == R_OUT)
		err = 1;
	else if (to_parse[i] == R_OUT && to_parse[i + 1] == R_IN)
		err = 1;
	if (check_token_length(&to_parse[i]))
		return (-1);
	if (ft_strchr(R_COMBO, to_parse[i]) && err)
		return (-1);
	return (0);
}
