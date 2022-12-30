/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:53:07 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/30 04:19:33 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	data = ft_calloc(sizeof(t_data), 1);
	is_error(data, data, MALLOC_ERR);
	//is_str_valid(data, argv[1]);
	if (data -> status == 2)
		return (1);
	init_env(data, envp);
	init_cmd(data, argv[1]);
	free_all(data);
}
