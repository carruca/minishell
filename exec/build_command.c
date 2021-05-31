/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:12:46 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 21:13:15 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	build_command(t_cmd *cmd, t_shell *sh, t_exec *exec)
{
	args_have_quotes(cmd->args_lst, sh);
	exec->argc = ft_lstsize_if(cmd->args_lst, is_not_empty);
	exec->argv = ft_lsttoa_if(cmd->args_lst, ft_strdup, is_not_empty);
	exec->env = ft_lsttoa_if(sh->env_lst, join_env, is_env);
	if (*exec->argv)
		set_var("_", exec->argv[exec->argc - 1], &sh->env_lst, modify_value);
	exec->builtin = check_builtin(sh, exec->argc, exec->argv);
	if (exec->argc > 0 && !exec->builtin)
		exec->path = get_exe_path(exec->argv[0], sh);
	find_command(sh, exec);
	if (exec->path)
		free(exec->path);
	ft_free_tab(exec->argv);
	ft_free_tab(exec->env);
}
