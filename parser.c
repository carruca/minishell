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
	printf("--------*redir file = %s\n", tmp->file);
	printf("--------*redir type = %d\n", tmp->type);
}

void	print_arg(void *arg)
{
	char *tmp;

	tmp = arg;
	printf("--------*arg = %s\n", tmp);
}

void	print_command(void *command)
{
	t_cmd	*tmp;

	tmp = command;
	if (tmp)
	{
		printf("-----\\\n------*Command:\n");
		printf("-------\\\n");
		ft_lstiter(tmp->args_lst, print_arg);
		ft_lstiter(tmp->redir_lst, print_redir);
		if (tmp->pipe)
			printf("--------*pipe = %d\n", tmp->pipe);
	}
}

void	print_pipeline(void *pipeline)
{
	t_pip	*tmp;

	tmp = pipeline;
	if (tmp)
	{
		printf("#################################\n----*Pipeline:\n");
		ft_lstiter(tmp->cmd_lst, print_command);
	}
}

void	print_parse_tree(t_list *pipeline_lst)
{
	if (pipeline_lst)
	{
		printf("#################################\n");
		ft_lstiter(pipeline_lst, print_pipeline);
		printf("#################################\n");
		printf("#################################\n");
	}
}

/*
void	del_current_token(t_list **tkn_lst)
{
	t_list	*alst;

	alst = (*tkn_lst)->next;
	ft_lstdelone(*tkn_lst, free_token);
	(*tkn_lst) = alst;
}
*/
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

int parse_redir(t_list **tkn_lst, t_cmd *cmd, int id)
{
	t_token	*atkn;
	t_redir	*aredir;

	aredir = new_redirection(tkn_lst, id);
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

int	parse_pipe(t_list **tkn_lst, t_cmd *cmd, int *pipe)
{
	t_token	*atkn;

	*pipe = 1;
	del_current_token(tkn_lst);
	if (!(*tkn_lst))
	{
		print_syntax_error("newline", tkn_lst);
		free_command(cmd);
		return (0);
	}
	atkn = (*tkn_lst)->content;
	if (atkn->identifier != WORD)
	{
		print_syntax_error(atkn->token, tkn_lst);
		free_command(cmd);
		return (0);
	}
	return (1);
}

t_cmd	*parse_simple_command(t_list **tkn_lst)
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
			if (!parse_redir(tkn_lst, cmd, id))
				return (NULL);
		}
		else if (id == PIPE)
		{
			if (!parse_pipe(tkn_lst, cmd, &cmd->pipe))
				return (NULL);
			break ;
		}
	}
	return (cmd);
}

/*
void	parse_simple_command(t_list **tkn_lst, t_cmd *cmd)
{
	int		id;

	while (*tkn_lst && id != SCOLON)
	{
		id = ((t_token *)(*tkn_lst)->content)->identifier;
		if (id == WORD)
			parse_args(tkn_lst, &cmd->args_lst);
		else if (id == GREAT || id == DGREAT || id == LESS)
		{
			parse_redirection(tkn_lst, &cmd->redir_lst, id);
			if (!cmd->redir_lst)
			{
//				free_args_and_redir(&cmd->args_lst, &cmd->redir_lst);
				break ;
			}
		}
		else if (id == PIPE)
		{
			parse_pipe(tkn_lst, &cmd->pipe);
			if (!(*tkn_lst))
				free_command(cmd);
			break ;
		}
	}
}

t_cmd	*new_simple_command(t_list **tkn_lst)
{
//	t_token	*atkn;
	t_cmd	*cmd;
	char	stop_word;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	stop_word = 0;
	parse_simple_command(tkn_lst, cmd);
	if (!cmd->args_lst && !cmd->redir_lst)
	{
		free_command(cmd);
	}
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
*/

t_list	*parse_command(t_list **tkn_lst)
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
		acmd = parse_simple_command(tkn_lst);
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
		{
			print_syntax_error(atkn->token, tkn_lst);
			ft_lstclear(&pipeline_lst, free_pipeline);
		}
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
	print_parse_tree(pipeline_lst);
	ft_lstclear(&pipeline_lst, free_pipeline);
	return (pipeline_lst);
}
