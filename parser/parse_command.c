/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:47:16 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:47:44 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_command(t_list **tkn_lst, char *prompt)
{
	t_list	*cmd_lst;
	t_cmd	*acmd;
	t_token	*atkn;

	cmd_lst = NULL;
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		if (atkn->identifier == SCOLON)
		{
			del_current_token(tkn_lst);
			break ;
		}
		acmd = new_simple_command(tkn_lst, prompt);
		if (!acmd)
		{
			ft_lstclear(&cmd_lst, free_command);
			return (NULL);
		}
		ft_lstadd_back(&cmd_lst, ft_lstnew(acmd));
	}
	return (cmd_lst);
}
