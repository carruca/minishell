/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:24:56 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:25:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		envp = get_env(name, sh->env_lst);
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
