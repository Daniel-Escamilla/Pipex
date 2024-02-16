SOURCE_FILES =	ft_main.c \
				ft_split.c \
				ft_commands.c \
				ft_pipex_utils.c \

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SOURCE_FILES:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

# bonus: all

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: clean all

git:
	git add .
	git status
	@read -p "Quieres continuar? [y/n]: " answer; \
	if [ "$$answer" = "y" ]; then \
		read -p "Mensaje para el commit: " message; \
		git commit -m "$$message"; \
		git push; \
	fi 

.PHONY: re fclean clean all
