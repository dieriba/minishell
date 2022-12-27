#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <unistd.h>
#include <errno.h>

# define IN_REDIRECTION "<"
# define OUT_REDIRECTION ">"

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
	char	*in;
	char	**out;
	char	*stop;
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

#endif MINISHELL_H