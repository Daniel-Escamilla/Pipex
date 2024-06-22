SOURCE_FILES =	ft_main.c \
				ft_split.c \
				ft_memset.c \
				ft_strrchr.c \
				ft_strjoin.c \
				ft_commands.c \

SOURCE_FILES_BONUS =	get_next_line.c \
						ft_main_bonus.c \
						ft_split_bonus.c \
						ft_childs_bonus.c \
						ft_command_bonus.c \
						ft_here_doc_bonus.c \
						get_next_line_utils.c \
						ft_pipex_utils_bonus.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SOURCE_FILES:.c=.o)
OBJECTS_BONUS = $(SOURCE_FILES_BONUS:.c=.o)

NAME = pipex

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

bonus: $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

git: fclean
	git add .
	git status
	@read -p "Quieres continuar? [y/n]: " answer; \
	if [ "$$answer" = "y" ]; then \
		read -p "Mensaje para el commit: " message; \
		git commit -m "$$message"; \
		git push; \
		clear; \
		echo "╔══════════════════════════════════════════════════════╗"; \
		echo "║ $(BOLD_GREEN)(┌ಠ_ಠ)\t ¡¡¡Git push realizado!!! \t(ಠ_ಠ┐)$(RESET) ║"; \
		echo "╚══════════════════════════════════════════════════════╝"; \
		sleep 0.5; \
		clear; \
	else \
		clear; \
		echo "╔════════════════════════════════════════════════════════╗"; \
		echo "║ $(BOLD_RED)(҂◕︵◕)\t¡¡¡Git push no realizado!!!\t (҂◕︵◕)$(RESET) ║"; \
		echo "╚════════════════════════════════════════════════════════╝"; \
		sleep 0.5; \
		clear; \
	fi


.PHONY: re fclean clean all bonus