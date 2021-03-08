NAME = minishell

SRCS = env main lista
OBJ_DIR = ./obj/
LIBFT_DIR = libft/
INCLUDE = -I include/

CC = gcc -g
WFLAGS = -Wall -Wextra -Werror
MAKE = make
RM = rm -rf

SRC = $(addsuffix .c, $(addprefix srcs/, $(SRCS))) \

%.o: %.c
	$(CC) $(WFLAGS) $(INCLUDE) -c $< -o $@

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[1;34m===> Compilando...\033[1;33m"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(WFLAGS) ./libft/libft.a -o $(NAME) $(OBJ)

clean:
	@echo  "\033[1;34m===> Borrando...\033[0;31m "
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)	

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run:
	@echo "\033[1;34m===> Ejecutando...\033[00m"
	@./minishell

.PHONY: all clean fclean re
