#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>

# define R_IN '<'
# define R_OUT '>'
# define R_COMBO "<>"
# define STOP	"|& "
# define STOP_	"|&"
typedef struct t_line	t_line;
typedef struct t_data	t_data;

typedef struct t_line
{
    char	*line;
	t_line	*next;
	t_line	*prev;
}	t_line;

typedef struct t_env
{
	t_line	*first;
	t_line	*last;
	t_data	*data;
}	t_env;

typedef struct t_cmd
{
	char	*cmd;
	char	**args;
	char	*infile;
	char	**in;
	char	**out;
	char	stop;
	int		exec;
	t_data	*data;
}	t_cmd;

typedef struct t_data
{
	int		status;
	t_env	*env;
	t_cmd	**cmd;
	int		pipes[2];
}t_data;

void	init_cmd(t_data *data, char *to_process);
void	set_commands(t_cmd *cmd, char *to_parse);
void	set_redirect_cmd(t_cmd *cmd, char *to_parse, char redirect);

#endif