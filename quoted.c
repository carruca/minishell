/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:06:58 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/06 14:48:34 by tsierra-         ###   ########.fr       */
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

int	count_env(char *name)
{
	char	*envp;

	envp = getenv(name);
	if (!envp)
		return (0);
   	return (ft_strlen(envp));
}

char	*get_env_name(char *str, int *i)
{
	char	*envp;
	int		envc;
	int		j;
	int		z;

	j = *i;
	envc = 0;
	while (!ft_strchr(" $\'\"\0", str[*i]))
	{
		(*i)++;
		envc++;
	}
	envp = malloc(sizeof(char) *envc + 1);
	if (!envp)
		return (NULL);
	z = 0;
	while (z < envc)
	{
		envp[z] = str[j];
		z++;
		j++;
	}
	envp[z] = '\0';
	return (envp);
}

void	count_expander(char *str, int *i, int *counter)
{
	char	*envp;

	(*i)++;
	envp = get_env_name(str, i);
//	printf("envp = %s\n", envp);
	*counter += count_env(envp);
	free(envp);
//	(*i)++;
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
		if (str[i] && str[i] == '$' && (quoted == 0 || quoted == 0x01))
			count_expander(str, &i, &counter);
		else if ((quoted || (str[i] != '\'' && str[i] != '\"')) && str[i])
		{
			counter++;
			i++;
		}
	}
//	printf("counter = %d\n", counter);
	return (counter);
}

void	copy_env(char *dst, char *name, int *j)
{
	int		i;
	char	*envp;

	envp = getenv(name);
	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		dst[*j] = envp[i];
		(*j)++;
		i++;
	}
}

void	copy_expander(char *dst, char *src, int *i, int *j)
{
	char	*envp;

	(*i)++;
	envp = get_env_name(src, i);
	copy_env(dst, envp, j);
	free(envp);
//	(*i)++;
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
		if (src[i] == '$' && (quoted == 0 || quoted == 0x01))
		{
//			printf("quoted = %d\n", quoted);
			copy_expander(dst, src, &i, &j);
//			printf("Busca variable\n");
//			printf("src[i] = %c\n", src[i]);
		}
		else if ((quoted || (src[i] != '\'' && src[i] != '\"')) && src[i])
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
//	dst[j] = '\0';
}

char	*strtrim_quotes(char *str)
{
	char	*dst;
	int		len;

	if (!str)
		return (NULL);
	len = count_without_quotes(str);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	copy_without_quotes(dst, str);
	dst[len] = '\0';
//	printf("dst = %s\n", dst);
	return (dst);
}

void	change_content(t_list *lst, void *content)
{
	void	*ptr;

	ptr = lst->content;
//	printf("content = %s\n", (char *)content);
	lst->content = content;
	free(ptr);
}

void	redir_file_have_quotes(char **str)
{
	char	*new;
	char	*ptr;

	if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"') || ft_strchr(*str, '$'))
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
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"') || ft_strchr(str, '$'))
		{
			new = strtrim_quotes(str);
//			printf("new = %s\n", new);
			change_content(lst, new);
		}
		lst = lst->next;
	}
}
