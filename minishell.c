/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:53:07 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 05:07:24 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_collector	*g_collector = NULL;

char	**clean_nl_str(t_data *data, char *line)
{
	size_t	i;
	size_t	j;
	int		seen;

	i = -1;
	seen = 0;
	while (line[++i])
	{
		if (line[i] == '\n' && !find_end_quotes(data, line, i))
		{
			j = i;
			while (line[++j] && line[j] != '\n')
				if (!ft_isspace(line[j]))
					seen = 1;
			if (seen == 0)
				line[i] = ' ';
		}
		else if (line[i] == '\n' && find_end_quotes(data, &line[i], i))
			line[i] *= -1;
	}
	return (ft_split(line, '\n'));
}

void	back_to_normal(char **line)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
		{
			if (line[i][j] == '\n' * -1)
				line[i][j] = '\n';
		}
	}
}

void	shell_routine(t_data *data)
{
	size_t	i;

	i = -1;
	ft_free_elem((void **)&data -> cp_to_parse);
	back_to_normal(data -> tab_);
	while (data -> tab_[++i])
	{
		data -> cp_to_parse = data -> tab_[i];
		init_cmd(data, data -> cp_to_parse);
		open_here_doc(data, data -> cmds);
		fork_docs(data, &data -> here_docs);
		close_all_pipes(data, &data -> here_docs, 0, 1);
		executing(data, data -> cmds, 0);
		clean_struct(data);
	}
	ft_free_tab(data -> tab_);
	data -> tab_ = NULL;
}

void	lets_read(t_data *data)
{
	char	*rescue_cmd;
	int		err;

	rescue_cmd = NULL;
	while (1)
	{
		data -> cp_to_parse = readline("bash  : ");
		if (data -> cp_to_parse)
		{
			err = valid_quotes(data, data -> cp_to_parse);
			if (err == 0)
				err = unvalid_line(data, data -> cp_to_parse, &rescue_cmd);
			add_history(data -> cp_to_parse);
			quote_to_neg(data, data -> cp_to_parse);
			if (err == 0)
			{
				data -> tab_ = clean_nl_str(data, data -> cp_to_parse);
				is_error(data, data -> tab_, MALLOC_ERR, 0);
				shell_routine(data);
			}
			if (data -> cp_to_parse)
				ft_free_elem((void **)&data -> cp_to_parse);
			
		}
		else
			free_all(data, 130);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	if (isatty(STDIN_FILENO) == 0)
		return (1);
	init_struct(&data);
	if (argc == 2)
		populate(data, argv[1]);
	init_env(data, envp);
	lets_read(data);
}
