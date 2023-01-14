/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:53:07 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/14 17:22:34 by dtoure           ###   ########.fr       */
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
	//handle_signals((*data));
}

void	lets_read(t_data *data)
{
	while (1)
	{
		data -> cp_to_parse = readline("minishell  : ");
		//quoted_str(data, data -> cp_to_parse);
		if (ft_strlen(data -> cp_to_parse))
		{
			//is_str_valid(data, data -> cp_to_parse);
			add_history(data -> cp_to_parse);
			init_cmd(data, data -> cp_to_parse);
			open_here_doc(data, data -> cmds);
			fork_docs(data, &data -> here_docs);
			close_all_pipes(data, &data -> here_docs, 0, 1);
			executing(data, data -> cmds, 0);
			clean_struct(data);
		}
		else if (!data -> cp_to_parse)
			free_all(data, 130, 0);
	}
}

void	shell(t_data *data, char **envp)
{
	init_env(data, envp);
	lets_read(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	init_struct(&data);
	data-> envp = envp;
	shell(data, envp);
}
