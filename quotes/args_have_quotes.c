/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_have_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:26:23 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:26:24 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	args_have_quotes(t_list *lst, t_shell *sh)
{
	char	*new;
	char	*str;

	while (lst)
	{
		str = lst->content;
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"') || ft_strchr(str, '$'))
		{
			new = trim_quotes(str, sh);
			change_content(lst, new);
		}
		lst = lst->next;
	}
}
