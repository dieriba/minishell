/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:30:18 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 11:33:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_export(t_data *data, t_cmd *cmd, char **tab)
{
	size_t	i;
	int		fd;

	fd = where_to_write(data, cmd);
	i = -1;
	cmd -> exit_status = 1;
	while (tab[++i])
	{
		if (ft_putstr_fd("export ", fd) < 0)
			return (print_err_built_in(cmd, "syscall", 1));
		if (ft_putendl_fd(tab[i], fd) < 0)
			return (print_err_built_in(cmd, "syscall", 1));
	}
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	cmd -> exit_status = 0;
	return (0);
}

char	*is_valid_export(char **tab, char *line)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (tab[++j])
		if (tab[j][0] == line[0] && !ft_strcmp(tab[j], line))
			return (NULL);
	while (line[++i] && line[i] != '=')
		;
	if (line[i] == 0 && check_line(line) == 0)
		return (NULL);
	line[i] = 0;
	if (ft_strlen(line) == 0 || check_line(line))
	{
		line[i] = '=';
		return (line);
	}
	line[i] = '=';
	return (&line[i]);
}

void	export_error(t_data *data, char *line)
{
	int	saved_stdout;
	int	saved_stderr;

	saved_stderr = dup(STDERR_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0 || saved_stderr < 0)
		print_err_and_exit(data, NULL, "syscall", 1);
	dup_and_close(data, STDERR_FILENO, STDOUT_FILENO, STDERR_FILENO);
	if (ft_printf("minishell : export: %s : not a valid identifier\n", line) < 0)
		print_err_and_exit(data, NULL, "syscall", 0);
	dup_and_close(data, saved_stdout, STDOUT_FILENO, saved_stdout);
	dup_and_close(data, saved_stderr, STDERR_FILENO, saved_stderr);
	data -> status = 1;
}

void	handle_export(t_data *data, t_cmd *cmd, t_env *env)
{
	char	*line;
	int		i;

	i = 0;
	while (cmd -> args[++i])
	{
		line = is_valid_export(env -> tab, cmd ->args[i]);
		if (line && line != cmd ->args[i])
			make_export(env, cmd -> args[i]);
		else if (line && line == cmd ->args[i])
			export_error(data, line);
	}
}

int	export(t_cmd *cmd, t_env *env)
{
	int		len;

	if (open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	cmd -> exit_status = 0;
	len = ft_tab_len(cmd -> args);
	if (len > 1 && (!ft_strcmp(cmd -> stop, "|")
			|| !ft_strcmp(cmd -> prev_stop, "|")))
		return (print_err_built_in(cmd, "minishell", -1));
	if (len == 1 && print_export(cmd -> data, cmd, env -> tab) == 0)
		return (1);
	else if (len > 1 && ft_strcmp(cmd -> stop, "|"))
		handle_export(cmd -> data, cmd, env);
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	return (1);
}
