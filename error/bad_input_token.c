/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 01:29:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/27 14:06:23 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_behind(t_data *data, char *to_parse, char *in, int j, int index)
{
	int	seen;

	seen = 1;
	while (--j > index)
	{
		while (j > index && ft_isspace(to_parse[j]))
			j--;
		if (!is_real_stop(data, to_parse, j, in))
			break ;
		else if (is_real_stop(data, to_parse, j, in))
		{
			seen = 0;
			break ;
		}
	}
	return (seen);
}

int	check_double(char *to_parse)
{
	size_t	i;

	i = -1;
	while (to_parse[++i])
	{
		if (to_parse[i] == R_IN && to_parse[i + 1] == R_OUT)
			return (to_parse[i]);
		else if (to_parse[i] == R_OUT && to_parse[i + 1] == R_IN)
			return (to_parse[i]);
	}
	return (0);
}

int	check_token_length(t_data *data, char *to_parse)
{
	size_t	i;
	int		len;

	i = -1;
	while (to_parse[++i])
	{
		len = 0;
		while (to_parse[i] && ft_isspace(to_parse[i]))
			i++;
		if (to_parse[i] && !is_real_stop(data, to_parse, i, DELIM_TOKEN_SP))
		{
			while (!is_real_stop(data, to_parse, ++i, DELIM_TOKEN_SP) && to_parse[i])
				len++;
			if (len > 0 && to_parse[i - 1] == ';')
				return (to_parse[i]);
			else if (len > 1)
				return (to_parse[i]);
		}
		if (to_parse[i] == 0)
			break ;
	}
	return (0);
}

int	check_validity(t_data *data, char *to_parse, size_t i, int both)
{
	int	flags;
	int	am_i_alone;

	flags = -1;
	am_i_alone = both;
	if (both)
		am_i_alone = check_behind(to_parse, DELIM_TOKEN_SP, i, -1);
	while (to_parse[++i] && ft_strchr(DELIM_TOKEN_SP, to_parse[i]))
		;
	while (to_parse[i])
	{
		if (!ft_strchr(DELIM_TOKEN_SP, to_parse[i]))
		{
			flags = 1;
			break ;
		}
		else if (!is_real_stop(data, to_parse, i, DELIM_TOKEN_SP))
			break ;
		i++;
	}
	if (flags == -1 || am_i_alone || !to_parse[i])
		return (-1);
	return (i);
}

int	valid_format_token(t_data *data, char *to_parse)
{
	size_t	i;
	int		flags;

	i = -1;
	flags = 0;
	while (to_parse[++i])
	{
		flags = 0;
		while (to_parse[i] && is_real_stop(data, to_parse, i, DELIM_TOKEN))
			i++;
		if (to_parse[i] && ft_strchr(STOP_, to_parse[i]))
			flags = check_validity(data, to_parse, i, 1);
		else if (to_parse[i] && ft_strchr(R_COMBO, to_parse[i]))
			flags = check_validity(to_parse, i, 0);
		if (to_parse[i] == 0 || flags == -1)
			break ;
		if (flags > 0)
			i = flags;
	}
	return (flags);
}

int	missing_right_commands(t_data *data, char *to_parse)
{
	size_t	i;
	int		seen;
	
	i = -1;
	while (to_parse[++i])
	{
		while (to_parse[i] && !is_real_stop(data, to_parse, i, BASE_STOP))
			i++;
		seen = 0;
		if (to_parse[i] && ft_strchr(BASE_FORMAT, to_parse[i]))
		{
			i += (to_parse[i] == to_parse[i + 1]);
			while (to_parse[++i] && ft_isspace(to_parse[i]))
				;
			if (to_parse[i])
				seen = 1;
			if (to_parse[i] == 0 && seen = 0)
				return (1);
		}
		i -= (to_parse[i] == 0);
	}
	return (0);
}

int	unvalid_line(char **line)
{
	
	return (0);
}