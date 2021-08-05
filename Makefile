SRCS		= revert.c
OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

NAME		= revert

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
CPPFLAGS	= -MMD

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

-include	$(DEPS)

clean:
			rm -f $(OBJS) $(DEPS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

#leaks --atExit -- ./revert revert.c
