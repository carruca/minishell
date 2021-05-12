#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "env.h"
# include "builtins.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <signal.h>
#include  <ctype.h>
#include <term.h>

typedef enum s_token_type
{
	TOKEN_LEFT_PAREN, 
	TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_QUOTE, 
	TOKEN_RIGHT_QUOTE,
	TOKEN_LEFT_DOUBLE_QUOTE, 
	TOKEN_RIGHT_DOUBLE_QUOTE,
	TOKEN_SEMICOLON, 
	TOKEN_REDIRECTION,
	TOKEN_PIPE, 
	TOKEN_DOLLAR, 
	TOKEN_CMD, 
	TOKEN_VAR, 
	TOKEN_STRING, 
	TOKEN_ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char			*start;
	int				len;
}					t_token;

#endif
