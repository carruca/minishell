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
	ft_strlcpy(envp, str + j, envc + 1);
	return (envp);
}

int	count_expander(char *str, int *i, int *counter)
{
	char	*envp;
	int		env_len;

	(*i)++;
	envp = get_env_name(str, i);
	env_len =count_env(envp);
	*counter += env_len;
	free(envp);
	return (env_len);
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
			copy_expander(dst, src, &i, &j);
		else if ((quoted || (src[i] != '\'' && src[i] != '\"')) && src[i])
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
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
	return (dst);
}

void	change_content(t_list *lst, void *content)
{
	void	*ptr;

	ptr = lst->content;
	lst->content = content;
	free(ptr);
}

void	print_redir_error(char *redirect, char *prompt)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(redirect, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

int	redir_file_have_quotes(char **str, char *prompt)
{
	char	*new;
	char	*ptr;

	if (str[0][0] == '$')
	{
		print_redir_error(*str, prompt);
		return (0);
	}
	else if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"') || ft_strchr(*str, '$'))
	{
		new = strtrim_quotes(*str);
		ptr = *str;
		*str = new;
		free(ptr);
	}
	return (1);
}

int	args_have_quotes(t_list *lst)
{
	char	*new;
	char	*str;

	while (lst)
	{
		str = lst->content;
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"') || ft_strchr(str, '$'))
		{
			new = strtrim_quotes(str);
			if (new[0] == '\0')
				printf("Entra\n");
			change_content(lst, new);
		}
		lst = lst->next;
	}
	return (1);
}
