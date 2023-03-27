/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:24:51 by dtoure            #+#    #+#             */
/*   Updated: 2023/03/27 13:57:55 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_bad_syntax(t_data *data, char *str, char token)
{
	add_history(data -> cp_to_parse);
	ft_putstr_fd(str, 2);
	ft_putchar_fd(token, 2);
	ft_putchar_fd('\n', 2);
	data -> status = 2;
	return (1);
}

void	print_err(char *str, t_cmd *cmd, int type, struct stat *sb)
{
	if (cmd && (stat(cmd -> args[0], sb) == 0 && S_ISDIR(sb -> st_mode)))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd -> args[0]);
		cmd -> data -> status = 127;
	}
	else if (cmd && (errno == 2 && cmd -> no_path))
		ft_printf("minishell: %s: command not found\n", cmd -> args[0]);
	else if (cmd && (errno == 2 && !cmd -> no_path))
		ft_printf("minishell: %s: No such file or directory\n", cmd -> args[0]);
	else if (type)
		perror("minishel");
	else
		ft_printf("%s\n", str);
}

void	print_err_and_exit(t_data *data, t_cmd *cmd, char *err_msg, int type)
{
	struct stat	sb;

	close_both_pipes(data, data -> pipes, &data -> inited);
	close_fd(data, "minishell", &data -> prev_pipes);
	print_err(err_msg, cmd, type, &sb);
	if (errno == 2)
		data -> status = 127;
	free_all(data, data -> status);
}

void	is_error(t_data *data, void *elem, char *err_msg, int type)
{
	if (!elem)
		print_err_and_exit(data, elem, err_msg, type);
}
