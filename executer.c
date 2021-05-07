/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:48:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/06 15:38:55 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "parser.h"
#include "token.h"
#include "quoted.h"

void	print_directory_error(char *dir_name, char *prompt)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(dir_name, 2);
	ft_putstr_fd(": is a directory\n", 2);
}

int		is_directory(char *path)
{
	DIR	*dirp;

	dirp = opendir(path);
	if (!dirp)
		return (0);
	closedir(dirp);
	return (1);
}

void	find_command(t_cmd *cmd, char *prompt)
{
	char	**argv;
	char	*path;

	args_have_quotes(cmd->args_lst);
	argv = ft_lsttoa(cmd->args_lst);
	path = get_exe_path(argv[0]);
	if (!path)
	{
		if (*argv[0] != '\0')
			print_command_error(argv[0], prompt);
	}
	else if (is_directory(path))
		print_directory_error(argv[0], prompt);
	else
		executer_command(path, argv);
	if (path)
		free(path);
	ft_free_tab(argv);
}

void	print_file_error(char *file, char *prompt)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	set_redir_fd(t_list *redir_lst, int *fd, char *prompt)
{
	t_redir		*aredir;

	ft_bzero(fd, sizeof(fd));
	while (redir_lst)
	{
		aredir = redir_lst->content;
		if(!redir_file_have_quotes(&aredir->file, prompt))
		{
			fd[0] = -1;
			break;
		}
		if (aredir->type == LESS)
			fd[0] = open(aredir->file, O_RDONLY);
		else if (aredir->type == GREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else if (aredir->type == DGREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (fd[0] == -1 || fd[1] == -1)
		{
			print_file_error(aredir->file, prompt);
			break ;
		}
		redir_lst = redir_lst->next;
	}
}

void	executer_pipeline(t_pip *pipeline, char *prompt, t_fd *fd)
{
	t_list	*head_lst;
	t_cmd	*acmd;

	head_lst = pipeline->cmd_lst;
	while (pipeline->cmd_lst)
	{
		acmd = pipeline->cmd_lst->content;
		set_redir_fd(acmd->redir_lst, fd->redir_fd, prompt);
		set_std_fd(fd, 0);
		fd->piped = 0;
		if (pipeline->cmd_lst->next)
			set_pipe(fd->fd, &fd->piped);
		set_std_fd(fd, 1);
		if (acmd->args_lst && fd->redir_fd[0] != -1 && fd->redir_fd[1] != -1)
			find_command(acmd, prompt);
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
	ft_lstclear(&head_lst, free_command);
}

void	executer(t_list *pipeline_lst, char *prompt)
{
	t_list	*alst;
	t_pip	*apipeline;
	t_fd	fd;

	alst = pipeline_lst;
	ft_bzero(&fd, sizeof(t_fd));
	while (alst)
	{
		cpy_std_fd(fd.std_fd);
		apipeline = alst->content;
		if (apipeline)
			executer_pipeline(apipeline, prompt, &fd);
		reset_std_fd(fd.std_fd);
		alst = alst->next;
	}
	ft_lstclear(&pipeline_lst, free_pipeline);
}
/*
void	executer_pipeline(t_pip *pipeline, char *prompt)
{
	t_list	*head_lst;
	t_list	*redir_aux;
	t_cmd	*acmd;
	t_redir	*aredir;
	int		fd[2];
	int		piped;
	int		fd_std_tmp[2];

	cpy_std_fd(fd_std_tmp);
	piped = 0;
	head_lst = pipeline->cmd_lst;
	while (pipeline->cmd_lst)
	{
		acmd = pipeline->cmd_lst->content;
		redir_aux = acmd->redir_lst;
		if (!piped)
			fd[0] = dup(fd_std_tmp[0]);
		piped = 0;
		while (redir_aux)
		{
			aredir = redir_aux->content;
			if (aredir->type == LESS)
				fd[0] = open(aredir->file, O_RDONLY);
			redir_aux = redir_aux->next;
		}
		redir_aux = acmd->redir_lst;
		set_std_fd(fd, 0);
		if (pipeline->cmd_lst->next)
		{
			pipe(fd);
			piped = 1;
		}
		set_std_fd(fd, 1);
		redir_aux = acmd->redir_lst;
		if (!piped)
			fd[1] = dup(fd_std_tmp[1]);
		while (acmd->redir_lst)
		{
			aredir = acmd->redir_lst->content;
			if (aredir->type == GREAT)
				fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			else if (aredir->type == DGREAT)
				fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			acmd->redir_lst = acmd->redir_lst->next;
		}
		ft_lstclear(&redir_aux, free_redir);
		set_std_fd(fd, 1);
		if (acmd)
			find_command(acmd, prompt);
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
	ft_lstclear(&head_lst, free_command);
	reset_std_fd(fd_std_tmp);
}*/
