/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:56 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/05 05:53:19 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	where_to_write(t_data *data, t_cmd *cmd)
{
	int		fd;

	fd = 1;
	if (cmd -> last_out && cmd -> last_out -> fd > 0)
		fd = cmd -> last_out -> fd;
	else if (data -> inited && cmd -> p_close == 0)
		fd = data -> pipes[1];
	else
		fd = find_write_pipes(data -> s_pipes);
	if (fd < 0)
		return (1);
	return (fd);
}

int	check_line(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$'
			&& (line[i + 1] == '=' || !line[i]))
			return (1);
		if (line[i] != '_' && !ft_isalpha(line[i]))
			return (1);
	}
	return (0);
}

int	check_line_alias(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$'
			&& (line[i + 1] == '=' || !line[i]))
			return (1);
		if (!ft_strchr(ALIAS_AUTHORIZED, line[i])
			&& !ft_isalpha(line[i]))
			return (1);
	}
	return (0);
}