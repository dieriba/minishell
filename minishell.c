/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:53:07 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/01 17:20:35 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_data	*g_data;

void	lets_read(t_data *data)
{
	t_node	*node;

	while (1)
	{
		data -> cp_to_parse = readline("minishell  : ");
		//quoted_str(data -> cp_to_parse);
		if (ft_strlen(data -> cp_to_parse))
		{
			add_history(data -> cp_to_parse);
			//is_str_valid(data, data -> cp_to_parse);
			init_cmd(data, data -> cp_to_parse);
			//executing(data -> cmds);
		}
		if (!data -> cp_to_parse)
			free_all(data, 130);
		node = create_node(data -> cp_to_parse, 0);
		is_error(node, MALLOC_ERR, 1);
		node -> alloc = 1;
		ft_lst_add_front_s(data, &data -> collector, node);
	}
}

void	shell(t_data *data, char **envp)
{
	init_env(data, envp);
	lets_read(data);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//handle_signals();
	g_data = ft_calloc(sizeof(t_data), 1);
	g_data -> neg_single_start = '\'' * -1;
	g_data -> neg_single_end = '\'' * -2;
	g_data -> neg_double_start = '"' * -1;
	g_data -> neg_double_end = '"' * -2;
	is_error(g_data, MALLOC_ERR, 1);
	shell(g_data, envp);
}
