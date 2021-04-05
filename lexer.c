/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/05 17:51:30 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

void	is_quoted(char c, int *quoted)
{
	if (c == '\'' && (*quoted == 0 || *quoted == 0x01))
		*quoted ^= 0x01;
	else if (c == '\"' && (*quoted == 0 || *quoted == 0x02))
		*quoted ^= 0x02;
}

int	skip_to_delimiter(char *str, char *set, size_t *len)
{
	int		i;
	int		quoted;

	i = 0;
	*len = 0;
	quoted = 0;
	while (str[i] != '\0' && *str)
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
	t_list		*tkn_lst;
	int			start;
	size_t		len;
	int			i;

	start = 0;
	len = 0;
	i = 0;
	tkn_lst = NULL;
	while (input[start] != '\0')
	{
		i = skip_to_delimiter(input + start, " ><|;\t", &len);
		if (len != 0)
		{
			ft_lstadd_back(&tkn_lst,
				ft_lstnew(new_token(ft_substr(input, start, len))));
			if (!tkn_lst->content)
				return (NULL);
		}
		start += i;
	}
	return (tkn_lst);
}
