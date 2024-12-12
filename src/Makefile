NAME = ../pipex

SOURCE_FILES =  ft_main.c \
                ft_split.c \
                ft_memset.c \
                ft_strdup.c \
                ft_calloc.c \
                ft_strlcpy.c \
                ft_strrchr.c \
                ft_strjoin.c \
                ft_commands.c \

OBJECTS_DIR = ../pipex_objects

OBJECTS = $(patsubst %.c, $(OBJECTS_DIR)/%.o, $(SOURCE_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIR)/%.o: %.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
