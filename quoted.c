/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:06:58 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/10 17:53:24 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
#include "quoted.h"
#include "parser.h"
#include "executer.h"
*/
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

int	count_env(char *name, t_shell *sh)
{
	char	*envp;
	int		count;

	count = 0;
	if (*name == '?')
	{
		envp = ft_itoa(sh->status);
		count = ft_strlen(envp);
		free(envp);
	}
	else
	{
		envp = find_node(name, sh->_env.env_lst);
		if (!envp)
			return (0);
		count = ft_strlen(envp);
	}
   	return (count);
}

char	*get_env_name(char *str, int *i)
{
	char	*envp;
	int		envc;
	int		j;

	j = *i;
	envc = 0;
	if(str[*i] == '?')
	{
		(*i)++;
		envc++;
	}
	else
	{
		while (!ft_strchr(" $\'\"\0", str[*i]))
		{
			(*i)++;
			envc++;
		}
	}
	envp = malloc(sizeof(char) *envc + 1);
	if (!envp)
		return (NULL);
	ft_strlcpy(envp, str + j, envc + 1);
	return (envp);
}

int	count_expander(char *str, int *i, int *counter, t_shell *sh)
{
	char	*envp;
	int		env_len;

	(*i)++;
	envp = get_env_name(str, i);
	env_len = count_env(envp, sh);
	*counter += env_len;
	free(envp);
	return (env_len);
}

static int	count_without_quotes(char *str, t_shell *sh)
{
	int		counter;
	int		quoted;
	int		i;

	i = 0;
	quoted = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] == '\'' || str[i] == '\"')
			is_quoted_2(str[i], &quoted, &i);
		if (str[i] && str[i] == '$' && (quoted == 0 || quoted == 0x01)
				&& !ft_strchr("\'\"\0", str[i + 1]))
			count_expander(str, &i, &counter, sh);
		else if ((quoted || (str[i] != '\'' && str[i] != '\"')) && str[i])
		{
			counter++;
			i++;
		}
	}
	return (counter);
}

void	copy_env(char *dst, char *name, int *j, t_shell *sh)
{
	int		i;
	char	*envp;
	char	freed;

	freed = 0;
	if (*name == '?')
	{
		envp = ft_itoa(sh->status);
		freed = 1;
	}
	else
		envp = find_node(name, sh->_env.env_lst);
	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		dst[*j] = envp[i];
		(*j)++;
		i++;
	}
	if (freed)
		free(envp);
}

void	copy_expander(char *dst, char *src, int *i, int *j, t_shell *sh)
{
	char	*envp;

	(*i)++;
	envp = get_env_name(src, i);
	copy_env(dst, envp, j, sh);
	free(envp);
}

static void	copy_without_quotes(char *dst, char *src, t_shell *sh)
{
	int		quoted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quoted = 0;
	while (src[i])
	{
		while (src[i] == '\'' || src[i] == '\"')
			is_quoted_2(src[i], &quoted, &i);
		if (src[i] == '$' && (quoted == 0 || quoted == 0x01)
				&& !ft_strchr("\'\"\0", src[i + 1]))
			copy_expander(dst, src, &i, &j, sh);
		else if (src[i] && (quoted || (src[i] != '\'' && src[i] != '\"')))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
}

char	*strtrim_quotes(char *str, t_shell *sh)
{
	char	*dst;
	int		len;

	if (!str)
		return (NULL);
	len = count_without_quotes(str, sh);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	copy_without_quotes(dst, str, sh);
	dst[len] = '\0';
	return (dst);
}

void	change_content(t_list *lst, void *content)
{
	void	*ptr;

	ptr = lst->content;
	lst->content = content;
	free(ptr);
}

int	redir_file_have_quotes(char **str, t_shell *sh)
{
	char	*new;
	char	*ptr;

	if (str[0][0] == '$')
	{
		print_error(sh, *str, "ambiguous redirect", 1);
		return (0);
	}
	else if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"') || ft_strchr(*str, '$'))
	{
		new = strtrim_quotes(*str, sh);
		ptr = *str;
		*str = new;
		free(ptr);
	}
	return (1);
}

void	args_have_quotes(t_list *lst, t_shell *sh)
{
	char	*new;
	char	*str;

	while (lst)
	{
		str = lst->content;
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"') || ft_strchr(str, '$'))
		{
			new = strtrim_quotes(str, sh);
			change_content(lst, new);
		}
		lst = lst->next;
	}
}
