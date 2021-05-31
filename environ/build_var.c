/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:19:48 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:19:49 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_var(char **str, t_list **env_lst, int (*f)())
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	extract_var(str, &name, &value);
	set_var(name, value, env_lst, f);
	restore_env(str);
	return (1);
}
