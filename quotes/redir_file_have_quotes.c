/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file_have_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:27:09 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:27:10 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_file_have_quotes(char **str, t_shell *sh)
{
	char	*new;
	char	*ptr;

	if (str[0][0] == '$')
	{
		print_error(sh, *str, "ambiguous redirect", 1);
		return (0);
	}
	else if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"') || ft_strchr(*str, '$'))
	{
		new = trim_quotes(*str, sh);
		ptr = *str;
		*str = new;
		free(ptr);
	}
	return (1);
}
