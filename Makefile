NAME = minishell
LNAME = ./libft/libft.a

SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/

SRC = main.c \
	  lexer.c \
	  token.c \
	  parser.c \
	  parser_utils.c \
	  parser_free.c \
	  parser_print.c \
	  executer.c \
	  command.c \
	  fd.c \
	  quoted.c \
	  builtins/check.c \
	  builtins/cd.c \
	  builtins/exit.c \
	  environ.c \
	  create_var_array.c \
	  env.c \
	  free_var.c \
	  free_node.c \
	  search_var.c \
	  set_env.c \
	  ft_insert_node_fin.c \
	  ft_lst_new_lst.c \
	  add_node_before_last.c \
	  find_history.c \
	  find_node.c \
	  ft_delete_node.c \
	  lst_iter_lst.c \
	  ft_lst_size_lst.c \
	  ft_insert_node_ini.c \
	  export_builtin.c \
	  command_line.c \
	  next_line_key.c \
	  ft_putchar.c \
	  create_node.c \
	  cap_key_up.c \
	  cap_key_right.c\
	  cap_key_printable.c \
	  cap_key_left.c \
	  cap_key_down.c \
	  ft_strjoin_free.c \
	  cap_delete_char.c \
	  imprimir_lst.c

OBJ = $(SRC:.c=.o)
INC = -I. -I $(LIBFT_DIR)
LIBFT = -L $(LIBFT_DIR) -lft
TERMCAP = -ltermcap

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INC) -O0
LDFLAGS = #-g3 -fsanitize=address
MAKE = make
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LNAME)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME) $(LIBFT) $(TERMCAP)

$(LNAME): 
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)
	$(RM) tag

tag:
	ctags $(SRC) $(LIBFT_DIR)*.c

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
