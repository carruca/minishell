/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:46:50 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/24 21:19:36 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

/*
t_list	*parse_simple_command(t_list **tkn_lst)
{
	t_token	*atkn;
	t_list	*
	//		ft_lstadd_back(&pipeline_lst, ft_lstnew(new_pipeline(parse_command(tkn_lst)));
	return ();
}
*/

t_list	*parse_commands(t_list	**tkn_lst)
{
	t_list	*cmd_lst;
	t_token	*atkn;

	cmd_lst = NULL;
	atkn = (*tkn_lst)->content;
	while (atkn->identifier != SCOLON)
	{
		ft_lstadd_back(&cmd_lst, ft_lstnew(new_command(tkn_lst)));
	}
	if (atkn->identifier == SCOLON)
		del_current_token(tkn_lst);
	return (cmd_lst);
}

t_pip	*new_pipeline(t_list **tkn_lst)
{
	t_pip	*new_pipeline;

	new_pipeline = malloc(sizeof(t_pip));
	if (!new_pipeline)
		return (NULL);
	new_pipeline->cmd_lst = parse_commands(tkn_lst);
	return (new_pipeline);
}

void	del_current_token(t_list **tkn_lst)
{
	t_list	*alst;

	alst = (*tkn_lst)->next;
	ft_lstdelone(*tkn_lst, free_token);
	(*tkn_lst) = alst;
}

void	print_syntax_error(char *token, t_list **tkn_lst)
{
	printf("-minishell: syntax error near unexpected token `%s'\n", token);
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
		if (atkn->identifier != SCOLON)
		{
			ft_lstadd_back(&pipeline_lst,
					ft_lstnew(new_pipeline()));
			printf("command found\n");
			del_current_token(tkn_lst);
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
	ft_lstiter(tkn_lst, &print_token);
	pipeline_lst = parse_pipeline(&tkn_lst);
	return (pipeline_lst);
}
