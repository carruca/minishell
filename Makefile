NAME			= minishell
LNAME			= ./libft/libft.a

SRC_DIR			= src/
OBJ_DIR			= obj/
LIBFT_DIR		= libft/

EXECUTER_DIR	= exec/
EXECUTER_SRC	= executer.c \
				  execute_pipeline.c \
				  execute_fork.c \
				  fd.c \
				  build_exec.c \
				  wait_children.c \
				  free_exec.c \
				  set_redir.c \
				  is_directory.c \
				  is_not_empty.c \
				  check_error.c \
				  print_error.c \
				  get_exe_path.c \
				  search_directory.c

BUILTIN_DIR		= builtins/
BUILTIN_SRC		= execute.c \
				  check.c \
				  print_error.c \
				  is_valid_var.c \
				  cd.c \
				  exit.c \
				  echo.c \
				  env.c \
				  export.c \
				  pwd.c \
				  unset.c

ENVIRON_DIR		= environ/
ENVIRON_SRC		= add_var.c \
				  build_var.c \
				  cmp_var.c \
				  env_name_cmp.c \
				  extract_var.c \
				  extract_env.c \
				  free_var.c \
				  get_env.c \
				  increase_shlvl.c \
				  init_var.c \
				  is_env.c \
				  is_export.c \
				  join_env.c \
				  modify_value.c \
				  restore_env.c \
				  set_flag.c \
				  set_flags.c \
				  set_var.c \
				  init_envlst.c

QUOTES_DIR		= quotes/
QUOTES_SRC		= args_have_quotes.c \
				  change_content.c \
				  copy_without_quotes.c \
				  count_without_quotes.c \
				  is_quoted2.c \
				  redir_file_have_quotes.c \
				  trim_quotes.c

EXPANSER_DIR	= expanser/
EXPANSER_SRC	= copy_env.c \
				  copy_expander.c \
				  count_env.c \
				  count_expander.c \
				  get_env_name.c

PARSER_DIR		= parser/
PARSER_SRC		= parser.c \
				  parse_pipeline.c \
				  parse_command.c \
				  parse_pipe.c \
				  parse_args.c \
				  parse_redir.c \
				  new_pipeline.c \
				  new_simple_command.c \
				  new_redirection.c \
				  print_syntax_error.c \
				  free_pipeline.c \
				  free_command.c \
				  free_redir.c

LEXER_DIR		= lexer/
LEXER_SRC		= tokenizer.c \
				  skip_to_delimiter.c \
				  is_quoted.c \
				  new_token.c \
				  id_token.c \
				  free_token.c \
				  del_current_token.c

MAIN_SRC		= main.c \
				  parser_print.c \
				  error_malloc.c \
				  ft_insert_node_fin.c \
				  ft_lst_new_lst.c \
				  find_history.c \
				  free_node.c \
				  lst_iter_lst.c \
				  t_lst_size_lst.c \
				  ft_insert_node_ini.c \
				  ft_strjoin_free.c \
				  command_line.c \
				  next_line_key.c \
				  ft_putchar.c \
				  create_node.c \
				  cap_key_up.c \
				  cap_key_right.c \
				  cap_key_printable.c \
				  cap_key_left.c \
				  cap_key_down.c \
				  cap_delete_char.c

SRC				:= $(SRC) \
				   $(addprefix $(EXECUTER_DIR), $(EXECUTER_SRC)) \
				   $(addprefix $(BUILTIN_DIR), $(BUILTIN_SRC)) \
				   $(addprefix $(ENVIRON_DIR), $(ENVIRON_SRC)) \
				   $(addprefix $(QUOTES_DIR), $(QUOTES_SRC)) \
				   $(addprefix $(EXPANSER_DIR), $(EXPANSER_SRC)) \
				   $(addprefix $(PARSER_DIR), $(PARSER_SRC)) \
				   $(addprefix $(LEXER_DIR), $(LEXER_SRC)) \
				   $(MAIN_SRC)

OBJ				= $(SRC:.c=.o)
INC				= -I. -I$(LIBFT_DIR)
LIBFT			= -L $(LIBFT_DIR) -lft
TERMCAP			= -ltermcap

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror $(INC) -O3 $(COMMON)
DEBUG			= -g3
SANITIZE		= -fsanitize=address
COMMON			= 
LDFLAGS			= $(COMMON) 
MAKE			= make
RM				= rm -rf

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
