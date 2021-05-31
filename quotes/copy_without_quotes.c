/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_without_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:26:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:26:48 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_without_quotes(char *dst, char *src, t_shell *sh)
{
	int		quoted;
	t_pos		pos;

	ft_bzero(&pos, sizeof(t_pos));
	quoted = 0;
	while (src[pos.i])
	{
		if (src[pos.i] == '\'' || src[pos.i] == '\"')
			is_quoted_2(src[pos.i], &quoted, &pos.i);
		if (src[pos.i] == '$' && (quoted == 0 || quoted == 0x01)
				&& !ft_strchr("\'\"\0", src[pos.i + 1]))
			copy_expander(dst, src, &pos, sh);
		else if (src[pos.i] && ((quoted == 1 && src[pos.i] != '\"')
				|| (quoted == 2 && src[pos.i] != '\'')
				|| (src[pos.i] != '\'' && src[pos.i] != '\"')))
		{
			dst[pos.j] = src[pos.i];
			pos.i++;
			pos.j++;
		}
	}
}
