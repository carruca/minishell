/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:31:36 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 19:32:05 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenizer(char *input)
{
	t_list	*tkn_lst;
	t_lex	lex;

	tkn_lst = NULL;
	ft_bzero(&lex, sizeof(t_lex));
	while (input[lex.start] != '\0')
	{
		lex.i = skip_to_delimiter(input + lex.start, " ><|;\t", &lex.len);
		if (lex.len != 0)
		{
			ft_lstadd_back(&tkn_lst,
				ft_lstnew(new_token(ft_substr(input, lex.start, lex.len))));
			if (!tkn_lst->content)
				return (NULL);
		}
		lex.start += lex.i;
	}
	return (tkn_lst);
}
