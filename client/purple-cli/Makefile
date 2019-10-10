CC		= /usr/bin/g++
RM		= rm -f

CXXFLAGS 	= -Wall -Wextra -I./includes

SRCS 	= src/main.cpp
OBJS	= $(SRCS:.cpp=.o)

NAME	= purple-cli

$(NAME): $(OBJS)
	/usr/bin/g++ $(OBJS) -o $(NAME) $(CXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
