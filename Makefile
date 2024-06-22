RESET = \033[0m

# Regular
RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m

# Bold
BOLD_RED = \033[1;31m
BOLD_GREEN = \033[1;32m
BOLD_PURPLE = \033[1;35m

# More colors
B_C = \033[1;36m
YELLOW = \033[0;33m
BOLD_YELLOW = \033[1;33m
BLUE = \033[0;34m
BOLD_BLUE = \033[1;34m
MAGENTA = \033[0;35m
BOLD_MAGENTA = \033[1;35m
WHITE = \033[0;37m
BOLD_WHITE = \033[1;37m

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