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

CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror

OBJECTS_DIR = pipex_objects
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCE_FILES:.c=.o))
OBJECTS_BONUS = $(addprefix $(OBJECTS_DIR)/, $(SOURCE_FILES_BONUS:.c=.o))

NAME = pipex

all: $(NAME)

bonus: $(OBJECTS_BONUS)
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS_BONUS)

$(NAME): $(OBJECTS)
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

$(OBJECTS_DIR)/%.o: %.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(CC) $(CFLAGS) $<

link: $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all bonus link
