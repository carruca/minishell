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
	}
	exec->builtin = check_builtin(exec->argc, exec->argv[0]);
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

int		execute_fork(t_exec *exec, int fd_in, int *fd_next)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd_in)
			dup2(fd_in, 0);
		close(fd_next[0]);
		if (fd_next[1] != 1)
			dup2(fd_next[1], 1);
		if (exec->path && !exec->builtin)
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
	len_lst = ft_lstsize(cmd_lst);
	current = cmd_lst;
	while (current)
	{
		ft_bzero(&exec, sizeof(t_exec)); 
		build_exec(&exec, (t_cmd *)current->content, sh);
		if (current->next)
			pipe(fd_next);
		else
			fd_next[1] = 1;
		execute_fork(&exec, fd_in, fd_next);
		fd_in = fd_next[0];
		free_exec(&exec);
		current = current->next;
	}
	while (--len_lst)
		wait(NULL);
//	system("lsof -c minishell");
	return (0);
}
