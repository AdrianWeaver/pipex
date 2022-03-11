NAME		=	pipex

SRCS_PATH	=	./sources/
OBJS_PATH	=	./objects/

SRCS		=	main.c

OBJS		=	$(addprefix $(OBJS_PATH),$(SRCS:.c=.o))
DEPS		=	$(OBJS:.o=.d)

CC			=	gcc

CFLAGS		=	-MMD -Wall -Wextra -Werror -g3
INC			=	-I ./includes/\
				-I ./not_my_libft/includes/

NOTLIBFT	=	$(NOTLIBFT_PATH)libnotmylibft.a
NOTLIBFT_PATH = ./not_my_libft/

all:			$(NAME)

$(NAME):		$(OBJS) $(NOTLIBFT)
				$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(NOTLIBFT)

$(NOTLIBFT):
				@make -C $(NOTLIBFT_PATH)

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					@mkdir -p $(OBJS_PATH)
					$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:		
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

test:		re
			./pipex "toto" "sort" "cat -e" "zaza"
			@echo "Now printing zaza file"
			cat -e zaza

valgrind:	all
			valgrind ./pipex "toto" "ls -l" "wc -l" "zaza"

-include $(DEPS)
.PHONY:		all clean fclean re
