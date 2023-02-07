/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:23:12 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 13:58:41 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	lets_exec(t_data *data, int err)
{
	if (err == 0)
	{
		quote_to_neg(data, data -> cp_to_parse);
		data -> tab_ = clean_nl_str(data, data -> cp_to_parse);
		is_error(data, data -> tab_, MALLOC_ERR, 0);
		shell_routine(data);
	}
	if (data -> cp_to_parse)
		ft_free_elem((void **)&data -> cp_to_parse);
}

void	lets_read(t_data *data)
{
	char	*rescue_cmd;
	int		err;

	rescue_cmd = NULL;
	while (1)
	{
		directory(data);
		data -> cp_to_parse = readline(data -> curr_dir.pwd);
		if (ft_strlen(data -> cp_to_parse) > 0)
		{
			err = valid_quotes(data, data -> cp_to_parse);
			if (err == 0)
				err = unvalid_line(data, data -> cp_to_parse, &rescue_cmd);
			add_history(data -> cp_to_parse);
			lets_exec(data, err);
		}
		else if (data -> cp_to_parse == NULL)
			free_all(data, 130);
	}
}
