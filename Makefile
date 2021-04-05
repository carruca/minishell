NAME = minishell
LNAME = ./libft/libft.a

SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/

SRC = main.c \
	  parser.c \
	  parser_utils.c \
	  lexer.c \
	  token.c \
	  print_parse_tree.c \
	  free_parse_tree.c
OBJ = $(SRC:.c=.o)
INC = -I. -I $(LIBFT_DIR)
LIBFT = -L $(LIBFT_DIR) -lft

CC = gcc
WFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
MAKE = make
RM = rm -rf

all: $(NAME) $(LNAME)

$(NAME): $(OBJ)
	$(CC) $(WFLAGS) $(INC) $(LIBFT) $(OBJ) -o $(NAME)

%.o: %.c $(LNAME)
	$(CC) $(WFLAGS) -c -o $@ $<

$(LNAME): 
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)
	$(RM) tag

tag:
	ctags $(SRC)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
