/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/09 15:29:40 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	unget_char(t_src *src)
{
	if (src->pos < 0)
		return ;
	src->pos--;
}

char	get_next_char(t_src *src)
{
	char	next_char;

	next_char = 0;
	if (!src || src->buf)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	if (src->pos == INIT_SRC_POS)
		src->pos = -1;
	else
		next_char = src->buf[src->pos];
	if (++src->pos >= src->size)
	{
		src->pos = src->size;
		return (END_OF_LINE);
	}
	return (src->buf[src->pos]);
}

char	peek_char(t_src *src)
{
	long	pos;

	if (!src || !src->buf)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	pos = src->pos;
	if (pos == INIT_SRC_POS)
		pos++;
	pos++;
	if (pos >= src->size)
		return (END_OF_LINE);
	return (src->buf[pos]);
}

void	skip_white_spaces(t_src *src)
{
	char c;

	c = 0;
	if (!src || !src->buf)
		return ;
	while (((c = peek_char(src)) != END_OF_LINE) && (c == ' ' || c == '\t'))
		get_next_char(src);
}
