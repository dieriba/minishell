/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:53:07 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 14:23:09 by dtoure           ###   ########.fr       */
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
	int		skip;

	i = -1;
	skip = 0;
	ft_free_elem((void **)&data -> cp_to_parse);
	back_to_normal(data -> tab_);
	while (data -> tab_[++i])
	{
		data -> cp_to_parse = data -> tab_[i];
		init_cmd(data, data -> cp_to_parse);
		open_here_doc(data, data -> cmds);
		skip = fork_docs(data, &data -> here_docs);
		close_all_pipes(data, &data -> here_docs, 0, 1);
		if (skip == 0)
			executing(data, data -> cmds);
		clean_struct(data);
	}
	ft_free_tab(data -> tab_);
	data -> tab_ = NULL;
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
