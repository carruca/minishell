/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:50:04 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:50:29 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
