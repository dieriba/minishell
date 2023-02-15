/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:23:12 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/15 03:27:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**clean_nl_str(char *line)
{
	size_t	i;
	size_t	j;
	int		seen;

	i = -1;
	seen = 0;
	while (line[++i])
	{
		if ((line[i] == '"' && valid_double(line, i))
			|| line[i] == '\'')
			skip_(line, &i, line[i]);
		else if (line[i] == '\n')
		{
			j = i;
			while (line[++j] && line[j] != '\n')
				if (!ft_isspace(line[j]))
					seen = 1;
			if (seen == 0)
				line[i] = ' ';
		}
	}
	return (ft_split(line, '\n'));
}

void	lets_exec(t_data *data, int err)
{
	if (err == 0)
	{
		data -> tab_ = clean_nl_str(data -> cp_to_parse);
		ft_free_elem((void **)&data -> cp_to_parse);
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
			lets_exec(data, err);
		}
		else if (data -> cp_to_parse == NULL)
			free_all(data, 130);
	}
}
