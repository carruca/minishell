/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:48:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/26 19:36:26 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
#include "executer.h"
#include "parser.h"
#include "token.h"
#include "quoted.h"
*/

void	print_error(t_shell *sh, char *str, char *msg, int	status)
{
	ft_putstr_fd(sh->prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	sh->status = status;
}
/*
void	print_directory_error(char *dir_name, char *prompt, int *status)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(dir_name, 2);
	ft_putstr_fd(": is a directory\n", 2);
	*status = 127;
}*/

int		is_directory(char *path)
{
	DIR	*dirp;

	dirp = opendir(path);
	if (!dirp)
		return (0);
	closedir(dirp);
	return (1);
}

int		is_not_empty(char *str)
{
	return (str[0] != 0);
}
/*
void	check_executer(t_shell *sh, char *path, int argc, char **argv, char **env)
{
	if (!check_builtin(sh, argc, argv))
		sh->status = executer_command(sh, path, argv, env);
}*/

void	find_command2(t_shell *sh, t_exec *exec)
{
	if (!exec->path && exec->argv[0] && *exec->argv[0] && !exec->builtin)
		print_error(sh, exec->argv[0], "command not found", 127);
	else if (exec->path && is_directory(exec->path))
		print_error(sh, exec->argv[0], "is a directory", 126);
	else if (!exec->builtin)
		sh->status = executer_command(sh, exec);
}

void	build_command(t_cmd *cmd, t_shell *sh, t_exec *exec)
{
/*	int	argc;
	char	**argv;
	char	**env;
	char	*path;
	int	builtin;*/

	args_have_quotes(cmd->args_lst, sh);
	exec->argc = ft_lstsize_if(cmd->args_lst, is_not_empty);
	exec->argv = ft_lsttoa_if(cmd->args_lst, ft_strdup, is_not_empty);
//	expath = NULL;
	exec->env = ft_lsttoa_if(sh->env_lst, join_var, is_env);
	if (*exec->argv)
		set_var2("_", exec->argv[exec->argc - 1], &sh->env_lst, modify_value2);
	exec->builtin = check_builtin(sh, exec->argc, exec->argv);
	if (exec->argc > 0 && !exec->builtin)
		exec->path = get_exe_path(exec->argv[0], sh);
	find_command2(sh, exec);
	if (exec->path)
		free(exec->path);
	ft_free_tab(exec->argv);
	ft_free_tab(exec->env);
}
/*
void	find_command(t_cmd *cmd, t_shell *sh)
{
	int		argc;
	char	**argv;
	char	**env;
	char	*path;
	int		builtin;

	args_have_quotes(cmd->args_lst, sh);
	argc = ft_lstsize_if(cmd->args_lst, is_not_empty);
	argv = ft_lsttoa_if(cmd->args_lst, ft_strdup, is_not_empty);
	path = NULL;
	env = ft_lsttoa_if(sh->env_lst, join_var, is_env);
	if (*argv)
		set_var2("_", argv[argc - 1], &sh->env_lst, modify_value2);
	builtin = check_builtin(sh, argc, argv);
	if (argc > 0 && !builtin)
		path = get_exe_path(argv[0], sh);
	if (!path && argv[0] && *argv[0] && !builtin)
		print_error(sh, argv[0], "command not found", 127);
	else if (path && is_directory(path))
		print_error(sh, argv[0], "is a directory", 126);
	else if (!builtin)
		sh->status = executer_command(sh, path, argv, env);
	if (path)
		free(path);
	ft_free_tab(argv);
	ft_free_tab(env);
}*/
/*
void	print_file_error(char *file, char *prompt)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}*/

int	set_redir_fd(t_list *redir_lst, int *fd, t_shell *sh)
{
	t_redir		*aredir;

	ft_bzero(fd, sizeof(fd));
	while (redir_lst)
	{
		aredir = redir_lst->content;
		if(!redir_file_have_quotes(&aredir->file, sh))
		{
			fd[0] = -1;
			return (0);
		}
		if (aredir->type == LESS)
			fd[0] = open(aredir->file, O_RDONLY);
		else if (aredir->type == GREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else if (aredir->type == DGREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (fd[0] == -1 || fd[1] == -1)
		{
			print_error(sh, aredir->file, strerror(errno), 1);
			return (0);
		}
		redir_lst = redir_lst->next;
	}
	return (1);
}

void	executer_compound(t_list *cmd_lst, t_shell *sh, t_exec *exec)
{
	t_cmd	*cmd;

	cmd = cmd_lst->content;
	//build_command;
	//is builtin and !cmd_lst->next
	//pipe and redir
	//execute_command
	if (!set_redir_fd(cmd->redir_lst, exec->fd.redir_fd, sh))
		sh->status = 1;
	set_std_fd(&exec->fd, 0);
	exec->fd.piped = 0;
	if (cmd_lst->next)
		set_pipe(exec->fd.fd, &exec->fd.piped);
	set_std_fd(&exec->fd, 1);
	if (cmd->args_lst && exec->fd.redir_fd[0] != -1 && exec->fd.redir_fd[1] != -1)
		build_command(cmd, sh, exec);
}

void	executer_pipeline(t_pip *pipeline, t_shell *sh, t_exec *exec)
{
//	int	status;
	t_list	*head;
//	t_cmd	*acmd;
//	t_list	*pid_lst;

	head = pipeline->cmd_lst;
	while (pipeline->cmd_lst)
	{
		executer_compound(pipeline->cmd_lst, sh, exec);
/*		acmd = pipeline->cmd_lst->content;
		if (!set_redir_fd(acmd->redir_lst, fd->redir_fd, sh))
			sh->status = 1;
		set_std_fd(fd, 0);
		fd->piped = 0;
		if (pipeline->cmd_lst->next)
			set_pipe(fd->fd, &fd->piped);
		set_std_fd(fd, 1);
		if (acmd->args_lst && fd->redir_fd[0] != -1 && fd->redir_fd[1] != -1)
			find_command(acmd, sh);*/
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
//	wait(NULL);
//	waitpid(0, &status, 0);
//	ft_lstadd_back(&pid_lst, ft_lstnew(&status));
	ft_lstclear(&head, free_command);
}

void	executer(t_shell *sh)
{
	t_list	*head;
	t_pip	*apipeline;
	t_exec	exec;
//	t_fd	fd;

	head = sh->pipeline_lst;
	ft_bzero(&exec, sizeof(t_exec));
	//ft_bzero(&fd, sizeof(t_fd));
	while (sh->pipeline_lst)
	{
		cpy_std_fd(exec.fd.std_fd);
		apipeline = sh->pipeline_lst->content;
		if (apipeline)
			executer_pipeline(apipeline, sh, &exec);
		reset_std_fd(exec.fd.std_fd);
		sh->pipeline_lst = sh->pipeline_lst->next;
	}
	ft_lstclear(&head, free_pipeline);
}
