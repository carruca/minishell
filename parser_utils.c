/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:32:38 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/05 17:48:52 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_syntax_error(char *token, t_list **tkn_lst, char *prompt)
{
	printf("%s: syntax error near unexpected token `%s'\n", prompt, token);
	if (tkn_lst)
		ft_lstclear(tkn_lst, free_token);
}

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
	return (redir);
}

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

int	parse_redir(t_list **tkn_lst, t_cmd *cmd, int id, char *prompt)
{
	t_token	*atkn;
	t_redir	*aredir;

	aredir = new_redirection(tkn_lst, id, prompt);
	if (!aredir)
	{
		free_command(cmd);
		return (0);
	}
	ft_lstadd_back(&cmd->redir_lst, ft_lstnew(aredir));
	atkn = (*tkn_lst)->content;
	while (*tkn_lst && atkn->identifier == WORD)
	{
		del_current_token(tkn_lst);
		if (*tkn_lst)
			atkn = (*tkn_lst)->content;
	}
	return (1);
}

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
	if (atkn->identifier != WORD)
	{
		print_syntax_error(atkn->token, tkn_lst, prompt);
		free_command(cmd);
		return (0);
	}
	return (1);
}
