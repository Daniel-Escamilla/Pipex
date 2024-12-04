SOURCE_FILES =	src/ft_main.c \
				src/ft_split.c \
				src/ft_memset.c \
				src/ft_strdup.c \
				src/ft_calloc.c \
				src/ft_strlcpy.c \
				src/ft_strrchr.c \
				src/ft_strjoin.c \
				src/ft_commands.c \

SOURCE_FILES_BONUS =	src_bonus/get_next_line.c \
						src_bonus/ft_main_bonus.c \
						src_bonus/ft_split_bonus.c \
						src_bonus/ft_strdup_bonus.c \
						src_bonus/ft_childs_bonus.c \
						src_bonus/ft_strlcpy_bonus.c \
						src_bonus/ft_command_bonus.c \
						src_bonus/ft_here_doc_bonus.c \
						src_bonus/get_next_line_utils.c \
						src_bonus/ft_pipex_utils_bonus.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

OBJECTS_DIR = pipex_objects
OBJECTS_DIR_BONUS = pipex_objects_bonus
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(notdir $(SOURCE_FILES:.c=.o)))
OBJECTS_BONUS = $(addprefix $(OBJECTS_DIR_BONUS)/, $(notdir $(SOURCE_FILES_BONUS:.c=.o)))

NAME = pipex

all: $(NAME)

bonus: $(OBJECTS_BONUS)
	@mkdir -p $(OBJECTS_DIR_BONUS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS_BONUS)

$(NAME): $(OBJECTS)
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

$(OBJECTS_DIR)/%.o: src/%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(CC) $(CFLAGS) $<

$(OBJECTS_DIR_BONUS)/%.o: src_bonus/%.c
	@mkdir -p $(OBJECTS_DIR_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS_DIR) $(OBJECTS_DIR_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all bonus
