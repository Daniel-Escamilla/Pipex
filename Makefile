SOURCE_FILES =	ft_main.c \
				ft_split.c \
				ft_strstr.c \
				ft_strjoin.c \
				ft_commands.c \

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SOURCE_FILES:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: re fclean clean all
