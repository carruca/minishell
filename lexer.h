/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:42:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/24 13:59:34 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "token.h"
# include <stdio.h>

t_list	*tokenizer(char *input);
int		skip_to_delimiter(char *str, char *set, size_t *lenght);
void	is_quoted(char c, int *quoted);

#endif
