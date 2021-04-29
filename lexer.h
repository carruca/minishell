/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:42:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/29 16:24:54 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "token.h"
# include <stdio.h>

typedef struct s_lex
{
	int	start;
	int	len;
	int	i;
}		t_lex;

t_list	*tokenizer(char *input);
int		skip_to_delimiter(char *str, char *set, int *len);
void	is_quoted(char c, int *quoted);

#endif
