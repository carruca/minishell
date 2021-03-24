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

t_cmd	*parse_cmd_and_args(t_list *tkn_lst)
{
	t_cmd	*cmd;

	cmd = NULL;
	while ()
	return (cmd);
}

t_list	*parse_pipeline(t_list *tkn_lst)
{
	t_token	*tmp;
	t_list	*pipeline_lst;

	tmp = tkn_lst->content;
	while (tmp)
	{
		if (tmp->identifier == WORD)
			pipeline = ft_lstadd_back(parse_cmd_and_args(tokens));
		if (tmp->identifier == SCOLON)
		ft_lstdelone(&tokens, &free_token);
		tmp = tkn_lst->content;
	}
	return (pipeline_lst);
}

t_list	*parser(char *input)
{
	t_list	*pipeline;
	t_list	*tkn_lst;

	pipeline = NULL;
	tkn_lst = tokenizer(input);
	return (pipeline);
}
