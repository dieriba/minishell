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
	char	**in;
	char	**out;
	char	**in_here_doc;
	char	**out_append;
	char	*last_in;
	char	*last_out;
	char	stop;
	int		exec;
	int		index; //for debug
	t_data	*data;
}	t_cmd;

typedef struct t_data
{
	int		status;
	int		out_redirection;
	int		in_redirection;
	t_env	*env;
	t_cmd	**cmds;
	int		pipes[2];
}t_data;

/*-----------------INITIALIZATION_UTILS-----------------*/
int		skip_spaces(char *to_parse, int i);
int		count_words(int length, char *to_parse);
/*-----------------INITIALIZATION_UTILS-----------------*/

/*-----------------INITIALIZATION-----------------*/
void	init_cmd(t_data *data, char *to_process);
void	set_commands(t_cmd *cmd, char *to_parse);
void	set_redirect_cmd(t_cmd *cmd, char *to_parse, char redirect);
void	set_heredoc_app_redirect(t_cmd *cmd, char *to_parse, char *redirect);
/*-----------------INITIALIZATION-----------------*/

/*-----------------FREE_STRUCT-----------------*/
void	free_list(t_line **head);
void	free_cmd(t_cmd **cmds);
/*-----------------FREE_STRUCT-----------------*/

/*-----------------ERROR_HANDLING-----------------*/
void	is_error(t_data *data, void *elem, char *err_msg);
/*-----------------ERROR_HANDLING-----------------*/


#endif