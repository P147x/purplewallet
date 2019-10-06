CC		= clang
RM		= rm -f

CFLAGS 	= -Wall -Wextra -I./includes

SRCS 	= src/main.cpp
OBJS	= $(SRCS:.cpp=.o)

NAME	= purple-cli

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
