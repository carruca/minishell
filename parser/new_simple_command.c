/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:44:14 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:44:51 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_simple_command(t_list **tkn_lst, char *prompt)
{
	t_cmd	*cmd;
	int		id;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	id = 0;
	while (*tkn_lst && id != SCOLON)
	{
		id = ((t_token *)(*tkn_lst)->content)->identifier;
		if (id == WORD)
			parse_args(tkn_lst, &cmd->args_lst);
		else if (id == GREAT || id == DGREAT || id == LESS)
		{
			if (!parse_redir(tkn_lst, cmd, id, prompt))
				return (NULL);
		}
		else if (id == PIPE)
		{
			if (!parse_pipe(tkn_lst, cmd, &cmd->pipe, prompt))
				return (NULL);
			break ;
		}
	}
	return (cmd);
}
