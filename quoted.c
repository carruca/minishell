/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:06:58 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/03 16:28:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "quoted.h"
#include "parser.h"

static void	is_quoted_2(char c, int *quoted, int *i)
{
	if (c == '\"' && (*quoted == 0 || *quoted == 0x01))
	{
		*quoted ^= 0x01;
		(*i)++;
	}
	else if (c == '\'' && (*quoted == 0 || *quoted == 0x02))
	{
		*quoted ^= 0x02;
		(*i)++;
	}
}

static int	count_without_quotes(char *str)
{
	int		counter;
	int		quoted;
	int		i;

	i = 0;
	quoted = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			is_quoted_2(str[i], &quoted, &i);
		if ((quoted || (str[i] != '\'' && str[i] != '\"')) && str[i])
		{
			counter++;
			i++;
		}
	}
	return (counter);
}

static void	copy_without_quotes(char *dst, char *src)
{
	int		quoted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quoted = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
			is_quoted_2(src[i], &quoted, &i);
		if ((quoted || (src[i] != '\'' && src[i] != '\"')) && src[i])
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
}

char	*strtrim_quotes(char *str)
{
	char	*dst;

	if (!str)
		return (NULL);
	dst = malloc(sizeof(char) * count_without_quotes(str) + 1);
	if (!dst)
		return (NULL);
	copy_without_quotes(dst, str);
	return (dst);
}

void	change_content(t_list *lst, void *content)
{
	void	*ptr;

	ptr = lst->content;
	lst->content = content;
	free(ptr);
}

void	redir_file_have_quotes(char **str)
{
	char	*new;
	char	*ptr;

	if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"'))
	{
		new = strtrim_quotes(*str);
		ptr = *str;
		*str = new;
		free(ptr);
	}
}

void	args_have_quotes(t_list *lst)
{
	char	*new;
	char	*str;

	while (lst)
	{
		str = lst->content;
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		{
			new = strtrim_quotes(str);
			change_content(lst, new);
		}
		lst = lst->next;
	}
}
