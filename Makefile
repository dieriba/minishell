SRCS		= 	minishell.c \
				print.c

SRCS_INIT	=	./init/init_cmds.c \
				./init/init_files.c \
				./init/init.c \
				./init/init_utils.c \
				./init/init_redirection.c \
				./init/init_env.c \
				./init/init_env_utils.c

SRCS_ERROR	=	./error/error_handling.c

SRCS_CLEAN	=	./clean/free.c

INCLUDES	= 	-I ./includes

OBJS		= 	$(SRCS:.c=.o) \
				$(SRCS_INIT:.c=.o) \
				$(SRCS_ERROR:.c=.o) \
				$(SRCS_CLEAN:.c=.o) \

DEPS		= 	$(SRCS:.c=.d) \
				$(SRCS_INIT:.c=.d) \
				$(SRCS_ERROR:.c=.d) \
				$(SRCS_CLEAN:.c=.d) \

CC			=	cc

CFLAGS		=   -Wall -Wextra -Werror -MMD

MINISHELL	=	minishell

all:			$(MINISHELL)

.c.o :	
				$(CC) -g3 $(CFLAGS) -c $< -o $@

$(MINISHELL):	${OBJS}
				make -C ./libft/ft_printf
				cp ./libft/ft_printf/libprintf.a ./lib
				make -C ./libft
				cp ./libft/libft.a ./lib
				make -C ./libft/get_next_line
				cp ./libft/get_next_line/libgnl.a ./lib
				$(CC) $(CFLAGS) ${OBJS} $(INCLUDES) -g3 -L./lib -lft -lprintf -lgnl -o $(MINISHELL)


clean:
				rm -rf $(OBJS)
				rm -rf $(DEPS)
			
fclean:			clean
				make -C ./libft/ft_printf fclean
				make -C ./libft/get_next_line fclean
				make -C ./libft/ fclean
				rm -rf $(MINISHELL) ./lib/libprintf.a ./lib/libgnl.a ./lib/libft.a 
				

re:				fclean all

-include : 		$(DEPS)

.PHONY:			all clean fclean re