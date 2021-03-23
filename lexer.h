/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:42:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/23 18:52:15 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"
#include <stdio.h>

# define WORD	0x01
# define LESS	0x02
# define GREAT	0x04
# define DGREAT	0x08
# define PIPE	0x10
# define SCOLON	0x20

typedef struct s_word
{
	char	*word;
	int		flags;
}			t_word_desc;

typedef struct s_token
{
	char	*token;
	int		identifier;
}			t_token;
/*
typedef enum e_control_operator
{
	PIPE,
	DSEMI,
	LESS,
	GREAT,
	DGREAT,
	STDOUT,
	STDIN
}	t_control;

typedef struct s_simple_command
{
	char		*cmd;
	int			token_counter;
	char		*name;
	char		**token_vector;
//	int			argc;
	char		**argv;
//	char		*path;
//	t_control	control;
}				t_simple;

typedef struct s_compound_command
{
	char		*cmd;
	int			simple_counter;
	t_simple	*simple; 	//Mejor una lista?
}				t_compound;
*/
t_list	*tokenizer(char *input);
int		skip_to_delimiter(char *str, char *set, size_t *lenght);
void	is_quoted(char c, int *quoted);
int		id_token(char *str);
t_token	*new_token(char *str);
void	free_token(void *tkn);
void	print_token(void *tkn);
#endif
