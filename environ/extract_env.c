/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:20:20 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/02 19:49:29 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*extract_env(char **env)
{
	t_list	*env_lst;

	env_lst = NULL;
	while (*env)
	{
		build_var(env, &env_lst, modify_value);
		env++;
	}
	return (env_lst);
}
