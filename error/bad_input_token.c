/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 01:29:31 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/29 04:23:51 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	check_token_length(char *to_parse)
{
	size_t	i;
	int		len;

	i = -1;
	while (to_parse[++i])
	{
		len = 0;
		if (ft_strchr(FORMAT_TOKEN, to_parse[i]))
		{
			while(ft_strchr(FORMAT_TOKEN, to_parse[++i]))
				len++;
			if (len > 1)
				return (to_parse[i]);	
		}
	}
	return (0);
}

int	check_validity(char *to_parse, size_t i)
{
	int	flags;
	int	am_i_alone;
	int	j;
	
	j = i;
	flags = -1;
	am_i_alone = 1;
	while (--j > -1 && !ft_strchr(FORMAT_TOKEN, to_parse[j]))
	{
		if (!ft_strchr(STOP_F, to_parse[j]))
		{
			am_i_alone = 0;
			break ;
		}
	}
	while(to_parse[++i])
	{
		if (!ft_strchr(FORMAT_TOKEN_SP, to_parse[i]))
		{
			flags = 1;
			break ;
		}
	}
	if (flags == -1 || am_i_alone || !to_parse[i])
		return (-1);
	return (i);
}

int	valid_format_token(char *to_parse)
{
	size_t	i;
	int		flags;
	
	i = -1;
	while (to_parse[++i])
	{
		if (ft_strchr(FORMAT_TOKEN, to_parse[i]))
		{
			flags = check_validity(to_parse, i);
			if (flags == -1)
				return (to_parse[i]);
			i = flags;
		}
	}
	return (0);
}

int	is_str_valid(t_data *data, char *to_parse)
{
	int	err;

	err = valid_format_token(to_parse);
	printf("Err val is : %d\n", err);
	if (err)
		return (print_bad_syntax(data, TOKEN_SYNTAX_ERR, err));
	err = check_double(to_parse);
	printf("Err val ids : %d\n", err);
	if (err)
		return (print_bad_syntax(data, TOKEN_SYNTAX_ERR, err));
	err = check_token_length(to_parse);
	printf("Err val is : %d\n", err);
	if (err)
		return (print_bad_syntax(data, TOKEN_SYNTAX_ERR, err));
	return (0);
}