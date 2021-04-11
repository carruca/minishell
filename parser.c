/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:46:50 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/06 16:39:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

t_cmd	*new_simple_command(t_list **tkn_lst, char *prompt)
{
	t_cmd	*cmd;
	int		id;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
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

t_pip	*new_pipeline(t_list **tkn_lst, char *prompt)
{
	t_pip	*new_pipeline;

	new_pipeline = malloc(sizeof(t_pip));
	if (!new_pipeline)
		return (NULL);
	new_pipeline->cmd_lst = parse_command(tkn_lst, prompt);
	if (!new_pipeline->cmd_lst)
	{
		free_pipeline(new_pipeline);
		return (NULL);
	}
	return (new_pipeline);
}

t_list	*parse_pipeline(t_list **tkn_lst, char *prompt)
{
	t_token	*atkn;
	t_list	*pipeline_lst;
	t_pip	*apipeline;

	pipeline_lst = NULL;
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		if (atkn->identifier != SCOLON && atkn->identifier != PIPE)
		{
			apipeline = new_pipeline(tkn_lst, prompt);
			if (!apipeline)
			{
				ft_lstclear(&pipeline_lst, free_pipeline);
				return (NULL);
			}
			ft_lstadd_back(&pipeline_lst, ft_lstnew(apipeline));
		}
		else
		{
			print_syntax_error(atkn->token, tkn_lst, prompt);
			ft_lstclear(&pipeline_lst, free_pipeline);
		}
	}
	return (pipeline_lst);
}

t_list	*parser(char *input, char *prompt)
{
	t_list	*pipeline_lst;
	t_list	*tkn_lst;

	tkn_lst = tokenizer(input);
	pipeline_lst = parse_pipeline(&tkn_lst, prompt);
	if (!pipeline_lst)
		return (NULL);
//	print_parse_tree(pipeline_lst);
	return (pipeline_lst);
}
