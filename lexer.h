/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:42:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/16 16:29:58 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"
#include <stdio.h>

typedef enum e_control_operator
{
	PIPE,
	LESS,
	GREAT,
	GREATGREAT,
	STDOUT,
	STDIN
}	t_control;

typedef struct s_simple_command
{
	char		*cmd;
	int			token_counter;
	char		*name;
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

void	split_command_line(char *line);
void	split_compound_command(t_compound *compound);
size_t	get_delimiter_in_str(char *str, char *set);

#endif
