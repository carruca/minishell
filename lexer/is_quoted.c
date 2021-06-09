/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quoted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:29:29 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 19:30:39 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_quoted(char c, int *quoted)
{
	if (c == '\'' && (*quoted == 0 || *quoted == 0x01))
		*quoted ^= 0x01;
	else if (c == '\"' && (*quoted == 0 || *quoted == 0x02))
		*quoted ^= 0x02;
}
