/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:42:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/09 15:07:56 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define END_OF_LINE	-1
# define ERRCHAR		0
# define INIT_SRC_POS	-2

typedef struct s_source
{
	char	*buf;
	long	size;
	long	pos;
}			t_src;

void	unget_char(t_src *src);
char	get_next_char(t_src *src);
char	peek_char(t_src *src);
void	skip_white_spaces(t_src *src);

#endif
