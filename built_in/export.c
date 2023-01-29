/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:30:18 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 21:43:59 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(t_data *data, t_cmd *cmd, char **tab, int subshell)
{
	size_t	i;
	int		fd;

	fd = where_to_write(data, cmd, subshell);
	if (fd != STDOUT_FILENO)
		dup_and_close(data, fd, STDOUT_FILENO, fd);
	i = -1;
	while (tab[++i])
		if (ft_printf("export %s\n", tab[i]) < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
	data -> status = 0;
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
	if (ft_printf("bash : export: %s : not a valid identifier\n", line) < 0)
		print_err_and_exit(data, NULL, "syscall", 0);
	dup_and_close(data, saved_stdout, STDOUT_FILENO, saved_stdout);
	dup_and_close(data, saved_stderr, STDERR_FILENO, saved_stderr);
	data -> status = 1;
}

void	export(t_cmd *cmd, t_env *env, int fork, int subshell)
{
	int		len;
	char	*line;
	size_t	i;

	i = 0;
	len = ft_tab_len(cmd -> args);
	if (len == 1 && fork)
		print_export(cmd -> data, cmd, env -> tab, subshell);
	else if (len > 1 && fork == 0 && ft_strcmp(cmd -> stop, "|"))
	{
		while (cmd ->args[++i])
		{
			line = is_valid_export(env -> tab, cmd ->args[i]);
			if (line && line != cmd ->args[i])
				make_export(env, cmd -> args[i]);
			else if (line && line == cmd ->args[i])
				export_error(cmd -> data, line);
		}
	}
}
