/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/05 12:34:18 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
#include "lexer.h"
#include "token.h"
*/

void	is_quoted(char c, int *quoted)
{
	if (c == '\'' && (*quoted == 0 || *quoted == 0x01))
		*quoted ^= 0x01;
	else if (c == '\"' && (*quoted == 0 || *quoted == 0x02))
		*quoted ^= 0x02;
}

int	skip_to_delimiter(char *str, char *set, int *len)
{
	int		i;
	int		quoted;

	i = 0;
	*len = 0;
	quoted = 0;
	while (str[i] != '\0')
	{
		is_quoted(str[i], &quoted);
		if (ft_strchr(set, str[i]) && !quoted)
		{
			i += (*len == 0);
			*len += (*len == 0 && str[i - 1] != ' ' && str[i - 1] != '\t');
			*len += (str[i - 1] == str[i] && !ft_strchr(" \t|<;", str[i]));
			i += (str[i - 1] == str[i] && !ft_strchr(" \t|<;", str[i]));
			break ;
		}
		i++;
		(*len)++;
	}
	return (i);
}

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
