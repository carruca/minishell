/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:27:15 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:27:16 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_quotes(char *str, t_shell *sh)
{
	char	*dst;
	int		len;

	if (!str)
		return (NULL);
	len = count_without_quotes(str, sh);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	copy_without_quotes(dst, str, sh);
	dst[len] = '\0';
	return (dst);
}
