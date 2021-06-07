#include "../minishell.h"

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
	{
		print_error(sh, exec->argv[0], "command not found", 127);
		return (1);
	}
	else if (exec->path && is_directory(exec->path))
	{
		print_error(sh, exec->argv[0], "is a directory", 126);
		return (1);
	}
	return (0);
}

int		execute_fork(t_shell *sh, t_exec *exec, int fd_in, int *fd_next)
{
	pid_t	pid;

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
		if (exec->builtin)
			execute_builtin(sh, exec);
		else if (!check_error(sh, exec))
			execve(exec->path, exec->argv, exec->env);
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

int		execute_pipeline(t_shell *sh, t_list *cmd_lst)
{
	t_list	*current;
	t_exec	exec;
	int		len_lst;
	int		fd_in;
	int		fd_next[2];

	fd_in = 0;
//	ft_bzero(fd_next, sizeof(int) * 2);
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
//			set_redir_fd((((t_cmd *)current->content))->redir_lst, fd_next, sh);
//			if (fd_next[0] != 0)
//				fd_in = fd_next[0];
			execute_fork(sh, &exec, fd_in, fd_next);
			fd_in = fd_next[0];
		}
		free_exec(&exec);
		current = current->next;
	}
	while (len_lst--)
		wait(NULL);
//	system("lsof -c minishell");
	return (0);
}
