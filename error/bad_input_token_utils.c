/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:02:02 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/14 03:23:20 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_case(t_data *data, char **rescue_cmd, char **cmd, int err)
{
	char	*to_free;

	ft_free_elem((void **)cmd);
	if (err == 2)
		print_bad_syntax(data, TOKEN_EOF_ERR, err);
	else if (err > 2)
		print_bad_syntax(data, TOKEN_SYNTAX_ERR, err);
	if (err > 0)
	{
		to_free = data -> cp_to_parse;
		data -> cp_to_parse = ft_strjoin(
				data -> cp_to_parse, (*rescue_cmd), 0, 0);
		add_history(data -> cp_to_parse);
		is_error(data, data -> cp_to_parse, MALLOC_ERR, 0);
		ft_free_elem((void **)rescue_cmd);
		ft_free_elem((void **)&to_free);
	}
}

void	rescue_command(t_data *data, char **rescue_cmd, int err)
{
	char	*cmd;
	char	*to_free;
	
	to_free = NULL;
	while (1)
	{
		cmd = readline("cmd: ");
		if (cmd)
			err = valid_format_token(cmd);
		else
			err = 0;
		if (ft_strlen(cmd) > 0)
		{
			to_free = (*rescue_cmd);
			(*rescue_cmd) = ft_strjoin((*rescue_cmd), cmd, " ", 0);
			is_error(data, (*rescue_cmd), MALLOC_ERR, 0);
		}
		ft_free_elem((void **)&to_free);
		if (cmd == NULL || (err == 0 && cmd[0]) || err > 0)
			break ;
	}
	handle_case(data, rescue_cmd, &cmd, err);
}

int	check_behind(char *to_parse, int j)
{
	int	seen;

	if (to_parse[j] == '(' && j == 0)
		return (j);
	if (!ft_strchr(STOP_, to_parse[j])
		&& (to_parse[j] != '(' && to_parse[j] != ')'))
		return (0);
	seen = 1;
	if (j - 1 < 0)
		return (seen);
	if (to_parse[j] == '(' || to_parse[j] == ')')
		return (check_behind_par(to_parse, j));
	while (--j > -1 && ft_strchr(DELIM_TOKEN_SP, to_parse[j]))
		;
	while (j > -1 && ft_isspace(to_parse[j]))
		j--;
	if (!ft_strchr(DELIM_TOKEN_SP, to_parse[j])
		&& to_parse[j] != '(')
		seen = 0;
	return (seen);
}
