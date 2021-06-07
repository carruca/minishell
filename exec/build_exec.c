/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 21:07:44 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/07 21:19:58 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_exec(t_exec *exec, t_cmd *cmd, t_shell *sh)
{
	args_have_quotes(cmd->args_lst, sh);
	exec->argc = ft_lstsize_if(cmd->args_lst, is_not_empty);
	if (exec->argc)
	{
		exec->argv = ft_lsttoa_if(cmd->args_lst, ft_strdup, is_not_empty);
		if (exec->argv)
			exec->env = ft_lsttoa_if(sh->env_lst, join_env, is_env);
		else
			return (0);
		exec->builtin = check_builtin(exec->argc, exec->argv[0]);
		if (exec->argc > 0 && !exec->builtin)
			exec->path = get_exe_path(exec->argv[0], sh);
		if (*exec->argv)
			set_var("_", exec->argv[exec->argc - 1],
				&sh->env_lst, modify_value);
	}
	return (1);
}
