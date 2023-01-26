/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:53:07 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 03:38:26 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_collector	*g_collector = NULL;

void	init_struct(t_data **data)
{
	(*data) = ft_calloc(sizeof(t_data), 1);
	is_error((*data), (*data), MALLOC_ERR, 1);
	(*data)-> neg_single_start = '\'' * -1;
	(*data)-> neg_single_end = '\'' * -2;
	(*data)-> neg_double_start = '"' * -1;
	(*data)-> neg_double_end = '"' * -2;
	(*data)-> prev_pipes = -1;
	(*data)-> cp_to_parse = NULL;
	handle_signals((*data));
}

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
				if (line[j] != ' ' || line[j] != '\t')
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
	while (1)
	{
		data -> cp_to_parse = readline("minishell  : ");
		if (data -> cp_to_parse)
		{
			add_history(data -> cp_to_parse);
			quote_to_neg(data, data -> cp_to_parse);
			data -> tab_ = clean_nl_str(data, data -> cp_to_parse);
			is_error(data, data -> tab_, MALLOC_ERR, 0);
			shell_routine(data);
		}
		else
			free_all(data, 130);
	}
}

/*void	test_free(t_data *data, char *line)
{
	init_cmd(data, line);
	open_here_doc(data, data -> cmds);
	fork_docs(data, &data -> here_docs);
	close_all_pipes(data, &data -> here_docs, 0, 1);
	clean_struct(data);
	free_all(data, 0);
}*/

void	shell(t_data *data, char **envp, char *line)
{
	(void)line;
	init_env(data, envp);
	//test_free(data, line);
	lets_read(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	init_struct(&data);
	shell(data, envp, argv[1]);
}
