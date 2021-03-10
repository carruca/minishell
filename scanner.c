/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:06:46 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/10 17:47:39 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "scanner.h"
#include "lexer.h"

char	*tok_buf = NULL;
int		tok_bufsize = 0;
int		tok_bufindex = -1;
t_token	eof_token;

void	add_to_buf(char c)
{
	char *tmp;

	tmp = NULL;
	tok_buf[tok_bufindex++] = c;
	if (tok_bufindex >= tok_bufsize)
	{
		tmp = realloc(tok_buf, tok_bufsize*2);
		if (!tmp)
		{
			errno = ENOMEM;
			return ;
		}
		tok_buf = tmp;
		tok_bufsize *= 2;
	}
}

t_token	*create_token(char *str)
{
	return (tok);
}
