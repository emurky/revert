SRCS		= revert.c
OBJS		= $(SRCS:.c=.o)

NAME		= revert

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS) $(NAME)

re:			clean all
