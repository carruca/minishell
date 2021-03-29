/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:46:50 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/29 18:33:42 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void	print_redir(void *redir)
{
	t_redir	*tmp;

	tmp = redir;
	printf("redir file = %s\n", tmp->file);
	printf("redir type = %d\n", tmp->type);
}

void	print_arg(void *arg)
{
	char *tmp;

	tmp = arg;
	printf("arg = %s\n", tmp);
}

void	del_current_token(t_list **tkn_lst)
{
	t_list	*alst;

	alst = (*tkn_lst)->next;
	ft_lstdelone(*tkn_lst, free_token);
	(*tkn_lst) = alst;
}

void	free_redir(void *redir)
{
	t_redir	*tmp;

	tmp = redir;
	free(tmp->file);
	free(tmp);
}

void	free_command(void *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	ft_lstclear(&tmp->args_lst, free);
	ft_lstclear(&tmp->redir_lst, free_redir);
	free(tmp);
}

void	free_pipeline(void *pipeline)
{
	t_pip	*tmp;

	tmp = pipeline;
	ft_lstclear(&tmp->cmd_lst, free_command);
	free(tmp);
}

t_redir	*parse_redirection(t_list **tkn_lst, int type)
{
	t_redir	*redir;
	t_token	*atkn;

	del_current_token(tkn_lst);
	atkn = (*tkn_lst)->content;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(atkn->token);
	redir->type = type;
	return (redir);
}

t_cmd	*new_simple_command(t_list **tkn_lst)
{
	t_token	*atkn;
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		if (atkn->identifier == WORD)
			ft_lstadd_back(&cmd->args_lst,
					ft_lstnew(ft_strdup(atkn->token)));
		else if (atkn->identifier == PIPE)
		{
			cmd->pipe = 1;
			del_current_token(tkn_lst);
			break ;
		}
		else if (atkn->identifier == GREAT || atkn->identifier == DGREAT 
				|| atkn->identifier == LESS)
			ft_lstadd_back(&cmd->redir_lst,
					ft_lstnew(parse_redirection(tkn_lst, atkn->identifier)));
		else
			break ;
		del_current_token(tkn_lst);
	}
	ft_lstiter(cmd->args_lst, print_arg);
	ft_lstiter(cmd->redir_lst, print_redir);
	printf("pipe = %d\n", cmd->pipe);
	return (cmd);
}

t_list	*parse_command(t_list **tkn_lst)
{
	t_list	*cmd_lst;
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
		ft_lstadd_back(&cmd_lst, ft_lstnew(new_simple_command(tkn_lst)));	
		printf("Command found\n");
	}
	return (cmd_lst);
}

t_pip	*new_pipeline(t_list **tkn_lst)
{
	t_pip	*new_pipeline;

	new_pipeline = malloc(sizeof(t_pip));
	if (!new_pipeline)
		return (NULL);
	new_pipeline->cmd_lst = parse_command(tkn_lst);
	return (new_pipeline);
}

void	print_syntax_error(char *token, t_list **tkn_lst)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	ft_lstclear(tkn_lst, free_token);
}

t_list	*parse_pipeline(t_list **tkn_lst)
{
	t_token	*atkn;
	t_list	*pipeline_lst;

	pipeline_lst = NULL;
	atkn = NULL;
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		if (atkn->identifier != SCOLON && atkn->identifier != PIPE)
		{
			ft_lstadd_back(&pipeline_lst,
					ft_lstnew(new_pipeline(tkn_lst)));
			printf("Pipeline found\n");
		}
		else
			print_syntax_error(atkn->token, tkn_lst);
		ft_lstclear(&pipeline_lst, free_pipeline);
	}
	return (pipeline_lst);
}

t_list	*parser(char *input)
{
	t_list	*pipeline_lst;
	t_list	*tkn_lst;

	tkn_lst = tokenizer(input);
//	ft_lstiter(tkn_lst, &print_token);
	pipeline_lst = parse_pipeline(&tkn_lst);
	return (pipeline_lst);
}
