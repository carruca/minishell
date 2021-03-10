#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "lexer.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

typedef struct s_variable
{
	char	*name;
	char	*value;
	char	*exportstr;
	int		attributes;
	int		context;
}			t_var;

typedef enum e_token_type
{
	TOKEN_LEFT_QUOTE,
	TOKEN_RIGHT_QUOTE,
	TOKEN_LEFT_DOUBLE_QUOTE,
	TOKEN_RIGHT_DOUBLE_QUOTE,
	TOKEN_SEMICOLON,
	TOKEN_GREAT,
	TOKEN_GREATGREAT,
	TOKEN_LESS,
	TOKEN_PIPE, 
	TOKEN_ENV, 
	TOKEN_CMD,
	TOKEN_ARGS,
	TOKEN_OPTIONS,
	TOKEN_ERROR
}	token_type;

typedef struct s_token
{
	token_type	type;
	char		*start;
	int			len;
}				t_token;

void	print_prompt();
char	*read_command_line();
void	read_eval_print_loop();

#endif
