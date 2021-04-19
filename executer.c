/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:48:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/15 18:34:29 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include <stdio.h>

extern char **environ;

char	**arglst_to_argv(t_list *lst)
{
	char	**argv;
	int		argc;
	int		i;
	
	argc = ft_lstsize(lst);
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		argv[i] = ft_strdup((char *)lst->content);
		if (!argv[i])
		{
			ft_free_tab(argv);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
}

int		search_directory(char *path, char *name)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(path);
	if (!dirp)
		return (0);
	while (1)
	{
		dp = readdir(dirp);
		if (!dp)
			break ;
		if (!ft_strcmp(dp->d_name, name))
		{
			closedir(dirp);
			return (1);
		}
	}
	closedir(dirp);
	return (0);
}

char	*ft_strjoin_btwchar(char *s1, char *s2, char c)
{
	char	*dst;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, s1_len + 1);
	dst[s1_len] = c;
	ft_strlcpy(dst + s1_len + 1, s2, s2_len + 1);
	dst[s1_len + s2_len + 1] = '\0';
	return (dst);
}

char	*get_exe_path(char *name)
{
	char	*env_path;
	char	*dir_path;
	char	*exe_path;

	if (!name)
		return (NULL);
	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	env_path = ft_strdup(getenv("PATH"));
	dir_path = ft_strtok(env_path, ":");
	while (dir_path != NULL)
	{
		if (search_directory(dir_path, name))
		{
			exe_path = ft_strjoin_btwchar(dir_path, name, '/');
			free(env_path);
			return (exe_path);
		}
		dir_path = ft_strtok(NULL, ":");
	}
	free(env_path);
	return (NULL);
}

void	executer_command(char *path, char **argv)
{
	int		status;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
		return ;
	else if (child_pid == 0)
	{
		execve(path, argv, environ);
		exit(0);
	}
	waitpid(child_pid, &status, 0);
}

void	print_command_error(char *cmd, char *prompt)
{
	printf("%s: %s: command not found\n", prompt, cmd);
}

void	find_command(t_cmd *cmd, char *prompt)
{
	char	**argv;
	char	*path;

	argv = arglst_to_argv(cmd->args_lst);
	path = get_exe_path(argv[0]);
	if (!path)
		print_command_error(argv[0], prompt);
	else
	{
		executer_command(path, argv);
		free(path);
	}
	ft_free_tab(argv);
}

void	cpy_std_fd(int	*fd)
{
	fd[0] = dup(0);
	fd[1] = dup(1);
}

void	reset_std_fd(int *fd)
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	set_std_fd(int *fd, int id)
{
	dup2(fd[id], id);
	close(fd[id]);
}

void	executer_pipeline(t_pip *pipeline, char *prompt)
{
	t_list	*head_lst;
	t_list	*head_redir_lst;
//	t_list	*redir_aux;
	t_cmd	*acmd;
	t_redir	*aredir;
	int		fd[2];
	int		fd_std_tmp[2];

	cpy_std_fd(fd_std_tmp);
	head_lst = pipeline->cmd_lst;
	while (pipeline->cmd_lst)
	{
		acmd = pipeline->cmd_lst->content;
//		redir_aux = acmd->redir_lst;
//		if (!redir_aux)
//			fd[0] = dup(fd_std_tmp[0]);
/*		while (acmd->redir_lst)
		{
			aredir = acmd->redir_lst->content;
			if (aredir->type == LESS)
				fd[0] = open(aredir->file, O_RDONLY);
			else
				fd[0] = dup(fd_std_tmp[0]);
			acmd->redir_lst = acmd->redir_lst->next;
		}
		acmd->redir_lst = redir_aux;*/
//		ft_lstclear(&acmd->redir_lst, free_redir);
		set_std_fd(fd, 0);
		if (pipeline->cmd_lst->next)
			pipe(fd);
		else
		{
			head_redir_lst = acmd->redir_lst;
			if (!acmd->redir_lst)
				fd[1] = dup(fd_std_tmp[1]);
			while (acmd->redir_lst)
			{
				aredir = acmd->redir_lst->content;
				if (aredir->type == GREAT)
					fd[1] = open(aredir->file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
				else if (aredir->type == DGREAT)
					fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
				else
					fd[1] = dup(fd_std_tmp[1]);
				acmd->redir_lst = acmd->redir_lst->next;
			}
			ft_lstclear(&head_redir_lst, free_redir);
		}
		set_std_fd(fd, 1);
		if (acmd)
			find_command(acmd, prompt);
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
	ft_lstclear(&head_lst, free_command);
	reset_std_fd(fd_std_tmp);
}

void	executer(t_list *pipeline_lst, char *prompt)
{
	t_list	*head_lst;
	t_pip	*apipeline;

	head_lst = pipeline_lst;
	while (pipeline_lst)
	{
		apipeline = pipeline_lst->content;
		if (apipeline)
			executer_pipeline(apipeline, prompt);
		pipeline_lst = pipeline_lst->next;
	}
	ft_lstclear(&head_lst, free_pipeline);
}
