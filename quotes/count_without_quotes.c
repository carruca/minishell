/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_without_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:26:55 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:26:56 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_without_quotes(char *str, t_shell *sh)
{
	int		counter;
	int		quoted;
	int		i;

	i = 0;
	quoted = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			is_quoted_2(str[i], &quoted, &i);
		if (str[i] && str[i] == '$' && (quoted == 0 || quoted == 0x01)
				&& !ft_strchr("\'\"\0", str[i + 1]))
			count_expander(str, &i, &counter, sh);
		else if (str[i] && ((quoted == 1 && str[i] != '\"')
					|| (quoted == 2 && str[i] != '\'')
					|| (str[i] != '\'' && str[i] != '\"')))
		{
			counter++;
			i++;
		}
	}
	return (counter);
}
