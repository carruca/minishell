/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:34:36 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 19:34:58 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	id_token(char *str)
{
	int	id;

	id = WORD;
	if (*str == '>')
		id = GREAT;
	if (str[0] == '>' && str[1] == '>')
		id = DGREAT;
	else if (*str == '<')
		id = LESS;
	else if (*str == '|')
		id = PIPE;
	else if (*str == ';')
		id = SCOLON;
	return (id);
}
