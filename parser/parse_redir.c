/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:54:53 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:55:17 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redir(t_list **tkn_lst, t_cmd *cmd, int id, char *prompt)
{
	t_redir	*aredir;

	aredir = new_redirection(tkn_lst, id, prompt);
	if (!aredir)
	{
		free_command(cmd);
		return (0);
	}
	ft_lstadd_back(&cmd->redir_lst, ft_lstnew(aredir));
	return (1);
}
