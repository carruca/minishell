/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:53:25 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:53:48 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redirection(t_list **tkn_lst, int type, char *prompt)
{
	t_redir	*redir;
	t_token	*atkn;

	del_current_token(tkn_lst);
	if (!(*tkn_lst))
	{
		print_syntax_error("newline", tkn_lst, prompt);
		return (NULL);
	}
	atkn = (*tkn_lst)->content;
	if (atkn->identifier != WORD)
	{
		print_syntax_error(atkn->token, tkn_lst, prompt);
		return (NULL);
	}
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(atkn->token);
	redir->type = type;
	del_current_token(tkn_lst);
	return (redir);
}
