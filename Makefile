SRCS	=     ./init/init_cmds.c \
              ./init/init_files.c \
			  ./init/init.c \
			  ./init/init_utils.c \
			  minishell.c

INCLUDES	= 	-I ./includes

OBJS		= 	$(SRCS:.c=.o)

DEPS		= 	$(SRCS:.c=.d)

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