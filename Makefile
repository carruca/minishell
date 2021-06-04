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
	  fd.c \
	  error_malloc.c \
	  ft_insert_node_fin.c \
	  ft_lst_new_lst.c \
	  find_history.c \
	  free_node.c \
	  lst_iter_lst.c \
	  ft_lst_size_lst.c \
	  ft_insert_node_ini.c \
	  ft_strjoin_free.c \
	  command_line.c \
	  next_line_key.c \
	  ft_putchar.c \
	  create_node.c \
	  cap_key_up.c \
	  cap_key_right.c\
	  cap_key_printable.c \
	  cap_key_left.c \
	  cap_key_down.c \
	  cap_delete_char.c \
	  builtins/execute.c \
	  builtins/check.c \
	  builtins/print_error.c \
	  builtins/is_valid_var.c \
	  builtins/cd.c \
	  builtins/exit.c \
	  builtins/echo.c \
	  builtins/env.c \
	  builtins/export.c \
	  builtins/pwd.c \
	  builtins/unset.c \
	  environ/add_var.c \
	  environ/build_var.c \
	  environ/cmp_var.c \
	  environ/env_name_cmp.c \
	  environ/extract_var.c \
	  environ/extract_env.c \
	  environ/free_var.c \
	  environ/get_env.c \
	  environ/increase_shlvl.c \
	  environ/init_var.c \
	  environ/is_env.c \
	  environ/is_export.c \
	  environ/join_env.c \
	  environ/modify_value.c \
	  environ/restore_env.c \
	  environ/set_flag.c \
	  environ/set_flags.c \
	  environ/set_var.c \
	  environ/init_envlst.c \
	  quotes/args_have_quotes.c \
	  quotes/change_content.c \
	  quotes/copy_without_quotes.c \
	  quotes/count_without_quotes.c \
	  quotes/is_quoted2.c \
	  quotes/redir_file_have_quotes.c \
	  quotes/trim_quotes.c \
	  expanser/copy_env.c \
	  expanser/copy_expander.c \
	  expanser/count_env.c \
	  expanser/count_expander.c \
	  expanser/get_env_name.c \
	  exec/build_command.c \
	  exec/executer.c \
	  exec/execute_pipeline.c \
	  exec/executer_compound.c \
	  exec/executer_pipeline.c \
	  exec/find_command.c \
	  exec/is_directory.c \
	  exec/is_not_empty.c \
	  exec/print_error.c \
	  exec/set_redir_fd.c \
	  exec/add_pid.c \
	  exec/executer_command.c \
	  exec/get_exe_path.c \
	  exec/search_directory.c
#	  environ.c \
	  executer.c \
	  command.c \
	  quoted.c

OBJ = $(SRC:.c=.o)
INC = -I. -I $(LIBFT_DIR)
LIBFT = -L $(LIBFT_DIR) -lft
TERMCAP = -ltermcap

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INC) -O0 $(COMMON)
DEBUG	= -g3
SANITIZE = -fsanitize=address
COMMON = 
LDFLAGS = $(COMMON) 
MAKE = make
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LNAME)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(TERMCAP) $(LDFLAGS)

sanitize:	COMMON += $(SANITIZE) $(DEBUG)
sanitize:	all

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
