/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:25:34 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/02 20:08:10 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_name(char *str, int *i)
{
	char	*envp;
	int		envc;
	int		j;

	j = *i;
	envc = 0;
	if (str[*i] == '?')
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
	envp = malloc(sizeof(char) * envc + 1);
	if (!envp)
		return (NULL);
	ft_strlcpy(envp, str + j, envc + 1);
	return (envp);
}
