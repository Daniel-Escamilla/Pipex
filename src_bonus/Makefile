# Nombre del ejecutable
NAME = ../pipex

SOURCE_FILES_BONUS =    get_next_line.c \
                        ft_main_bonus.c \
                        ft_split_bonus.c \
                        ft_strdup_bonus.c \
                        ft_childs_bonus.c \
                        ft_strlcpy_bonus.c \
                        ft_command_bonus.c \
                        ft_here_doc_bonus.c \
                        get_next_line_utils.c \
                        ft_pipex_utils_bonus.c \

OBJECTS_DIR_BONUS = ../pipex_objects_bonus

OBJECTS_BONUS = $(patsubst %.c, $(OBJECTS_DIR_BONUS)/%.o, $(SOURCE_FILES_BONUS))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS_BONUS)
	@mkdir -p $(OBJECTS_DIR_BONUS)
	$($<)
	$(CC) $(OBJECTS_BONUS) -o $(NAME)

$(OBJECTS_DIR_BONUS)/%.o: %.c
	@mkdir -p $(OBJECTS_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
