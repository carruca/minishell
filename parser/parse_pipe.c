/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:55:36 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:56:00 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_list **tkn_lst, t_cmd *cmd, int *pipe, char *prompt)
{
	t_token	*atkn;

	*pipe = 1;
	del_current_token(tkn_lst);
	if (!(*tkn_lst))
	{
		print_syntax_error("newline", tkn_lst, prompt);
		free_command(cmd);
		return (0);
	}
	atkn = (*tkn_lst)->content;
	if (atkn->identifier & (PIPE | SCOLON))
	{
		print_syntax_error(atkn->token, tkn_lst, prompt);
		free_command(cmd);
		return (0);
	}
	return (1);
}
