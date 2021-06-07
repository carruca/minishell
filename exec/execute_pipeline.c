/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:25:08 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/07 18:51:57 by tsierra-         ###   ########.fr       */
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
	}
	if (exec->argc > 0 && !exec->builtin)
		exec->path = get_exe_path(exec->argv[0], sh);
	return (1);
}

void	free_exec(t_exec *exec)
{
	if (exec->argc)
		ft_free_tab(exec->argv);
	if (exec->env)
		ft_free_tab(exec->env);
	if (exec->path)
		free(exec->path);
}

static int	check_error(t_shell *sh, t_exec *exec)
{
	if (!exec->path && exec->argv[0] && *exec->argv[0] && !exec->builtin)
		return (print_error(sh, exec->argv[0], "command not found", 127));
	else if (exec->path && is_directory(exec->path))
		return (print_error(sh, exec->argv[0], "is a directory", 126));
	return (0);
}

int	set_redir(t_shell *sh, t_list *redir_lst)
{
	t_redir	*redir;
	int		fd_redir[2];

	ft_bzero(fd_redir, sizeof(int) * 2);
	while (redir_lst)
	{
		redir = redir_lst->content;
		if (!redir_file_have_quotes(&redir->file, sh))
			return (1);
		if (redir->type & LESS)
			fd_redir[0] = open(redir->file, O_RDONLY);
		else if (redir->type & GREAT)
			fd_redir[1] = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else if (redir->type & DGREAT)
			fd_redir[1] = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (fd_redir[0] == -1 || fd_redir[1] == -1)
			return (print_error(sh, redir->file, strerror(errno), 1));
		redir_lst = redir_lst->next;
	}
	if (fd_redir[0] > 2)
		dup2(fd_redir[0], 0);
	if (fd_redir[1] > 2)
		dup2(fd_redir[1], 1);
	return (0);
}

int	execute_fork(t_shell *sh, t_exec *exec, int fd_in, int *fd_next, t_cmd *cmd)
{
	pid_t	pid;
	int		fd_out;

	fd_out = 1;
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_in)
			dup2(fd_in, 0);
		close(fd_next[0]);
		if (fd_next[1] != 1)
			dup2(fd_next[1], 1);
		if (!set_redir(sh, cmd->redir_lst))
		{
			if (exec->builtin & EXIT_BUILTIN)
				;
			else if (exec->builtin)
				execute_builtin(sh, exec);
			else if (!check_error(sh, exec))
				execve(exec->path, exec->argv, exec->env);
		}
		close(fd_next[1]);
		exit(0);
	}
	else
	{
		if (fd_in)
			close(fd_in);
		if (fd_next[1] != 1)
			close(fd_next[1]);
	}
	return (0);
}

int	execute_pipeline(t_shell *sh, t_list *cmd_lst)
{
	t_list	*current;
	t_exec	exec;
	int		len_lst;
	int		fd_in;
	int		fd_next[2];

	fd_in = 0;
	len_lst = ft_lstsize(cmd_lst);
	current = cmd_lst;
	while (current)
	{
		ft_bzero(&exec, sizeof(t_exec)); 
		build_exec(&exec, (t_cmd *)current->content, sh);
		if (len_lst == 1 && exec.builtin)
			execute_builtin(sh, &exec);
		else if (exec.argc > 0)
		{
			if (current->next)
				pipe(fd_next);
			else
				fd_next[1] = 1;
			execute_fork(sh, &exec, fd_in, fd_next, (t_cmd *)current->content);
			fd_in = fd_next[0];
		}
		free_exec(&exec);
		current = current->next;
	}
	while (len_lst--)
		wait(NULL);
	//system("lsof -c minishell");
	return (0);
}
