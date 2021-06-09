/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:54:05 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:54:31 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(t_list **tkn_lst, t_list **args_lst)
{
	t_token	*atkn;

	atkn = (*tkn_lst)->content;
	while (*tkn_lst && atkn->identifier == WORD)
	{
		ft_lstadd_back(args_lst,
			ft_lstnew(ft_strdup(atkn->token)));
		del_current_token(tkn_lst);
		if (*tkn_lst)
			atkn = (*tkn_lst)->content;
	}
}
