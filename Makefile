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
	  cd.c \
	  exit.c

OBJ = $(SRC:.c=.o)
INC = -I. -I $(LIBFT_DIR)
LIBFT = -L $(LIBFT_DIR) -lft

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INC) -O0
LDFLAGS = #-g3 -fsanitize=address
MAKE = make
RM = rm -rf

all: $(NAME) $(LNAME)

$(NAME): $(OBJ) $(LNAME)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME) $(LIBFT)

#%.o: %.c $(LNAME)
#	$(CC) $(WFLAGS) -c -o $@ $<

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
