/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:00:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/06 14:09:15 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "lexer.h"
# include "token.h"
# include "parser.h"
# include "executer.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

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

void	print_prompt();
char	*read_command_line();
void	read_eval_print_loop();

#endif
