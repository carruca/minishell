#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_variable
{
	char	*name;
	char	*value;
	char	*exportstr;
	int		attributes;
	int		context;
}			t_var;

typedef struct s_token
{
	token_type	type;
	char			*start;
	int				len;
}					t_token;

typedef enum e_token_type
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
}	token_type;
#endif
