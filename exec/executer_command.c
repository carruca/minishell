/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:36:44 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 21:37:28 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executer_command(t_shell *sh, t_exec *exec)
{
//	int		status;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
		return (0);
	else if (child_pid == 0)
	{
//		tcsetattr(1, TCSANOW, &sh->term);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (exec->builtin)
			execute_builtin(sh, exec);
		else
			execve(exec->path, exec->argv, exec->env);
		exit(0);
	}
	sh->status = 0;
//	waitpid(child_pid, &status, 0);
	add_pid(child_pid, &sh->pid_lst);
//	while (waitpid(-1, NULL, WNOHANG) > 0)
//		;
//	tcsetattr(1, TCSAFLUSH, &sh->my_term);
//	tputs(tgetstr("ks", 0), 1, ft_putchar);
	return (0);
}
