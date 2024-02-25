SOURCE_FILES =	ft_main.c \
				ft_split.c \
				ft_strstr.c \
				ft_memset.c \
				ft_strjoin.c \
				ft_commands.c \

NAME = pipex

NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SOURCE_FILES:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

bonus:
	$(MAKE) -C bonus_pipex all
	mv bonus_pipex/pipex_bonus .

clean:
	rm -rf $(OBJECTS)
	$(MAKE) -C bonus_pipex clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: clean all bonus

git: fclean
	git add .
	git status
	@read -p "Quieres continuar? [y/n]: " answer; \
	if [ "$$answer" = "y" ]; then \
		read -p "Mensaje para el commit: " message; \
		git commit -m "$$message"; \
		git push; \
	fi 

.PHONY: re fclean clean all
