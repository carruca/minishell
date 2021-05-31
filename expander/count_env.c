/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:25:15 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:25:17 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		envp = get_env(name, sh->env_lst);
		if (!envp)
			return (0);
		count = ft_strlen(envp);
	}
   	return (count);
}
