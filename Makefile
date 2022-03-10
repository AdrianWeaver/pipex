NAME		=	pipex

SRCS_PATH	=	./sources/
OBJS_PATH	=	./objects/

SRCS		=	main.c

OBJS		=	$(addprefix $(OBJS_PATH),$(SRCS:.c=.o))
DEPS		=	$(OBJS:.o=.d)

CC			=	gcc

CFLAGS		=	-MMD -Wall -Wextra -Werror
INC			=	-I ./includes

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:		
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

-include $(DEPS)
.PHONY:		all clean fclean re
