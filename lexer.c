/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/23 18:47:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

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
			*len += (str[i - 1] == str[i] && str[i] != ' ' && str[i] != '\t');
			i += (str[i - 1] == str[i] && str[i] != ' ' && str[i] != '\t');
			break ;
		}
		i++;
		(*len)++;
	}
	return (i);
}
/*
size_t	get_delimiter_in_str(char *str, char *set)
{
	size_t			len;
	unsigned char	quates;

	len = 0;
	quates = 0;
	while (str[len] != '\0' && *str)
	{
		if (str[len] == '\"' && (quates == 0 || quates == 0x02))
			quates ^= 0x02;
		else if (str[len] == '\'' && (quates == 0 || quates == 0x01))
			quates ^= 0x01;
		else if (ft_strchr(set, str[len]) && !quates)
		{
			len++;
			if (str[len - 1] == '>' && str[len] == '>')
				len++;
			break ;
		}
		else if (str[len] == '\\' && !quates)
			len++;
		len++;
	}
	return (len);
}

int	count_simple_command(char *compound, char *set)
{
	int				counter;
	int				i;
	unsigned char	quates;

	counter = 1;
	i = 0;
	quates = 0;
	while (compound[i] != '\0')
	{
		if (compound[i] == '\"' && (quates == 0 || quates == 0x02))
			quates ^= 0x02;
		else if (compound[i] == '\'' && (quates == 0 || quates == 0x01))
			quates ^= 0x01;
		else if (ft_strchr(set, compound[i]) && !quates)
		{
			if (compound[i] == '>' && compound[i + 1] == '>')
				i++;
			counter++;
		}
		else if (compound[i] == '\\' && !quates)
			i++;
		i++;
	}
	return (counter);
}

void	split_simple_command(t_simple *simple, char **simple_command)
{
	int		i;
	char	*tmp;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	tmp = NULL;
	tmp = ft_strtrim(*simple_command, " ");
	printf("simple simple = %s\n", tmp);
	simple->token_counter = count_simple_command(tmp, " ");
	printf("token counter = %d\n", simple->token_counter);
	simple->token_vector = ft_calloc(simple->token_counter,
			sizeof (char *));
	while (i < simple->token_counter)
	{
		len = get_delimiter_in_str(tmp + start, " ");
		simple->token_vector[i] = ft_substr(tmp, start, len);
		printf("token = %s\n", simple->token_vector[i]);
		free(simple->token_vector[i]);
		i++;
		start += len;
	}
	free(simple->token_vector);
	free(tmp);
}

void	split_compound_command(t_compound *compound)
{
	int		start;
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	start = 0;
	len = 0;
	compound->simple_counter = 0;
	tmp = NULL;
	tmp = ft_strtrim(compound->cmd, " ");
	compound->simple_counter = count_simple_command(tmp, "<>|");
	printf("compound compound = $%s$\n", tmp);
	printf("simple counter = %d\n", compound->simple_counter);
	compound->simple = ft_calloc(compound->simple_counter, sizeof (t_simple));
	while (tmp[start] != '\0')
	{
		len = get_delimiter_in_str(tmp + start, "<>|");
		printf("len simple command = %d\n", len);
		compound->simple[i].cmd = ft_substr(tmp, start, len);
		printf("simple command = $%s$\n", compound->simple[i].cmd);
		split_simple_command(compound->simple, &compound->simple[i].cmd);
		free(compound->simple[i].cmd);
		i++;
		start += len;
	}
	free(tmp);
	free(compound->simple);
}
*/
/*
int	id_token(char *str)
{
	int	id;

	id = WORD;
	if (*str == '>')
		id = GREAT;
	if (str[0] == '>' && str[1] == '>')
		id = DGREAT;
	else if (*str == '<')
		id = LESS;
	else if (*str == '|')
		id = PIPE;
	else if (*str == ';')
		id = SCOLON;
	return (id);
}

t_token	*new_token(char *str)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->token = str;
	tkn->identifier = id_token(str);
	return (tkn);
}

void	free_token(void *tkn)
{
	t_token	*tmp;

	tmp = tkn;
	free(tmp->token);
	free(tmp);
}

void	print_token(void *tkn)
{
	t_token	*tmp;

	tmp = tkn;
	printf("token	= $%s$\n", tmp->token);
//	printf("id	= $0x%02x$\n", tmp->identifier);
}*/

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
			ft_lstadd_back(&tkn_lst,
					ft_lstnew(new_token(ft_substr(input, start, len))));
		start += i;
	}
	ft_lstiter(tkn_lst, &print_token);
	ft_lstclear(&tkn_lst, &free_token);
	return (tkn_lst);
}
