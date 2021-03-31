/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:46:50 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/31 16:50:52 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void	print_redir(void *redir)
{
	t_redir	*tmp;

	tmp = redir;
	printf("-------redir file = %s\n", tmp->file);
	printf("-------redir type = %d\n", tmp->type);
}

void	print_arg(void *arg)
{
	char *tmp;

	tmp = arg;
	printf("----arg = %s\n", tmp);
}

void	print_command(void *command)
{
	t_cmd	*tmp;

	tmp = command;
	printf("--Command:\n");
	ft_lstiter(tmp->args_lst, print_arg);
	ft_lstiter(tmp->redir_lst, print_redir);
	printf("----pipe = %d\n", tmp->pipe);
}

void	print_pipeline(void *pipeline)
{
	t_pip	*tmp;

	tmp = pipeline;
	printf("Pipeline:\n");
	ft_lstiter(tmp->cmd_lst, print_command);
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
	if (tmp->args_lst)
	{
		if (tmp->args_lst->content)
			ft_lstclear(&tmp->args_lst, free);
		else
			free(tmp->args_lst);
	}
	if (tmp->redir_lst)
	{
		if (tmp->redir_lst->content)
			ft_lstclear(&tmp->redir_lst, free_redir);
		else
			free(tmp->redir_lst);
	}
	free(tmp);
}

void	free_pipeline(void *pipeline)
{
	t_pip	*tmp;

	tmp = pipeline;
	if (tmp->cmd_lst)
	{
		if (tmp->cmd_lst->content)
			ft_lstclear(&tmp->cmd_lst, free_command);
		else
			free(tmp->cmd_lst);
	}
	free(tmp);
}

void	print_syntax_error(char *token, t_list **tkn_lst)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	if (tkn_lst)
		ft_lstclear(tkn_lst, free_token);
}

t_redir	*new_redirection(t_list **tkn_lst, int type)
{
	t_redir	*redir;
	t_token	*atkn;

	del_current_token(tkn_lst);
	if (!(*tkn_lst))
	{
		print_syntax_error("newline", tkn_lst);
		return (NULL);
	}
	atkn = (*tkn_lst)->content;
	if (atkn->identifier != WORD)
	{
		print_syntax_error(atkn->token, tkn_lst);
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

void	parse_redirection(t_list **tkn_lst, t_list **redir_lst, int id)
{
	t_token	*atkn;
	t_redir	*aredir;

	aredir = new_redirection(tkn_lst, id);
	if (!aredir)
		return ;
	ft_lstadd_back(redir_lst, ft_lstnew(aredir));
	atkn = (*tkn_lst)->content;
	printf("Entra\n");
	while (*tkn_lst && atkn->identifier == WORD)
	{
		del_current_token(tkn_lst);
		if (*tkn_lst)
			atkn = (*tkn_lst)->content;
	}
}

void	parse_pipe(t_list **tkn_lst, int *pipe)
{
	t_token	*atkn;

	*pipe = 1;
	del_current_token(tkn_lst);
	if (!(*tkn_lst))
	{
		print_syntax_error("newline", tkn_lst);
		return ;
	}
	atkn = (*tkn_lst)->content;
	if (atkn->identifier == PIPE)
		print_syntax_error(atkn->token, tkn_lst);
}

void	parse_simple_command(t_list **tkn_lst, t_cmd **cmd)
{
	t_token	*atkn;
	t_cmd	*acmd;
	int		id;

	acmd = *cmd;
	atkn = NULL;
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		id = atkn->identifier;
		if (id == WORD)
			parse_args(tkn_lst, &acmd->args_lst);
		else if (id == GREAT || id == DGREAT || id == LESS)
			parse_redirection(tkn_lst, &acmd->redir_lst, id);
		else if (id == PIPE)
		{
			parse_pipe(tkn_lst, &acmd->pipe);
			if (!(*tkn_lst))
			{
				free_command(acmd);
				return ;
			}
			break ;
		}
		else if (id == SCOLON)
			break ;
	}
}

t_cmd	*new_simple_command(t_list **tkn_lst)
{
	t_token	*atkn;
	t_cmd	*cmd;
	char	stop_word;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	stop_word = 0;
/*	parse_simple_command(tkn_lst, &cmd);
	if (!cmd)
		return (NULL);*/
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		if (atkn->identifier == WORD && !stop_word)
			ft_lstadd_back(&cmd->args_lst,
					ft_lstnew(ft_strdup(atkn->token)));
		else if (atkn->identifier == PIPE)
		{
			parse_pipe(tkn_lst, &cmd->pipe);
			if (!(*tkn_lst))
			{
				free_command(cmd);
				return (NULL);
			}
			break ;
		}
		else if (atkn->identifier == GREAT || atkn->identifier == DGREAT 
				|| atkn->identifier == LESS)
		{
			ft_lstadd_back(&cmd->redir_lst,
					ft_lstnew(new_redirection(tkn_lst, atkn->identifier)));
			if (!cmd->redir_lst->content)
			{
				free_command(cmd);
				return (NULL);
			}
			stop_word = 0x01;
		}
		else if (atkn->identifier == SCOLON)
			break ;
		if (*tkn_lst)
			del_current_token(tkn_lst);
	}
	return (cmd);
}

t_list	*parse_command(t_list **tkn_lst)
{
	t_list	*cmd_lst;
	t_cmd	*acmd;
	t_token	*atkn;

	cmd_lst = NULL;
	acmd = NULL;
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		if (atkn->identifier == SCOLON)
		{
			del_current_token(tkn_lst);
			break ;
		}
		acmd = new_simple_command(tkn_lst);
		if (!acmd)
		{
			ft_lstclear(&cmd_lst, free_command);
			return (NULL);
		}
		ft_lstadd_back(&cmd_lst, ft_lstnew(acmd));
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
	if (!new_pipeline->cmd_lst)
	{
		free_pipeline(new_pipeline);
		return (NULL);
	}
	return (new_pipeline);
}

t_list	*parse_pipeline(t_list **tkn_lst)
{
	t_token	*atkn;
	t_list	*pipeline_lst;
	t_pip	*apipeline;

	pipeline_lst = NULL;
	atkn = NULL;
	apipeline = NULL;
	while (*tkn_lst)
	{
		atkn = (*tkn_lst)->content;
		if (atkn->identifier != SCOLON && atkn->identifier != PIPE)
		{
			apipeline = new_pipeline(tkn_lst);
			if (!apipeline)
			{
				ft_lstclear(&pipeline_lst, free_pipeline);
				return (NULL);
			}
			ft_lstadd_back(&pipeline_lst, ft_lstnew(apipeline));
		}
		else
			print_syntax_error(atkn->token, tkn_lst);
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
	if (!pipeline_lst)
		return (NULL);
	ft_lstiter(pipeline_lst, print_pipeline);
	ft_lstclear(&pipeline_lst, free_pipeline);
	return (pipeline_lst);
}
