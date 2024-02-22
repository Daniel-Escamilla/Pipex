SOURCE_FILES_BONUS =	ft_childs.c \
						ft_main_bonus.c \
						ft_split_bonus.c \
						ft_commands_bonus.c \
						ft_pipex_utils_bonus.c \

NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

OBJECTS_BONUS = $(SOURCE_FILES_BONUS:.c=.o)

all: $(NAME_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS) : $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJECTS_BONUS)

clean:
	rm -rf $(OBJECTS_BONUS)

fclean: clean
	rm -rf $(NAME_BONUS)

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
