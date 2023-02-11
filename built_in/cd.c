/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:03:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 14:03:54 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_error(t_data *data, char *err_msg)
{
	if (ft_putendl_fd(err_msg, 2) < 0)
		print_err_and_exit(data, NULL, "syscall", 1);
}

int	is_absolute_path(char *path)
{
	size_t	i;
	int		abs;

	if (path == NULL)
		return (1);
	i = -1;
	abs = 0;
	while (path[++i])
	{
		if (path[i] == '/')
			abs = 1;
		else if (path[i] == '.')
			return (0);
	}
	if (abs)
		return (1);
	return (0);
}

int	update_prompt(t_data *data, char *path)
{
	char	*tmp;

	tmp	= getcwd(NULL, 0);
	if (tmp == NULL)
		print_err_built_in(NULL, CHDIR_ERROR GET_CWD_ERR, 1);
	ft_free_elem((void **)&tmp);
	if (chdir(path) < 0)
		return (print_err_built_in(NULL, "bash", 1));
	ft_free_elem((void **)&data -> curr_dir.dir_name);
	data -> curr_dir.dir_name = getcwd(NULL, 0);
	is_error(data, data -> curr_dir.dir_name, "bash", 1);
	data -> curr_dir.path = ft_strrchr(data -> curr_dir.dir_name, '/')
		+ (ft_strlen(data -> curr_dir.dir_name) > 1);
	data -> curr_dir.new_dir = 1;
	return (0);
}

int	cd(t_data *data, t_cmd *cmd)
{
	int		len;
	char	*path;

	if (close_redirection(cmd))
		return (1);
	if (!ft_strcmp(cmd -> stop, "|") || !ft_strcmp(cmd -> prev_stop, "|"))
		return (1);
	data -> status = 1;
	len = ft_tab_len(cmd -> args);
	if (len > 2)
		cd_error(data, "bash : cd : too many arguments");
	else if (len == 1)
		path = get_var_line(find_var(cmd -> data -> env -> tab, "HOME"));
	else
		path = cmd -> args[1];
	if (len == 1 && path == NULL)
		cd_error(data, "bash : cd : HOME not set");
	if ((len == 1 && path == NULL) || len > 2)
		return (1);
	if (update_prompt(data, path))
		return (1);
	data -> status = 0;
	return (1);
}
