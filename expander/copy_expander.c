/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:25:06 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:25:08 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_expander(char *dst, char *src, t_pos *pos, t_shell *sh)
{
	char	*envp;

	pos->i++;
	envp = get_env_name(src, &pos->i);
	copy_env(dst, envp, &pos->j, sh);
	free(envp);
}
