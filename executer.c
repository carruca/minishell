/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:48:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/21 17:25:29 by tsierra-         ###   ########.fr       */
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
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
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

void	set_redir_fd(t_list *redir_lst, int	*fd)
{
	t_list	*head_lst;
	t_redir	*aredir;

	head_lst = redir_lst;
	while (redir_lst)
	{
		aredir = redir_lst->content;
		if (aredir->type == LESS)
			fd[0] = open(aredir->file, O_RDONLY);
		if (aredir->type == GREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else if (aredir->type == DGREAT)
			fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		redir_lst = redir_lst->next;
	}
	ft_lstclear(&head_lst, free_redir);
}

void	executer_pipeline_2(t_pip *pipeline, char *prompt)
{
	t_list	*head_lst;
//	t_list	*redir_aux;
	t_cmd	*acmd;
//	t_redir	*aredir;
	int		fd[2];
//	int		aux[2];
	int		aux_fd[0];
	int		piped;
	int		fd_std_tmp[2];

	cpy_std_fd(fd_std_tmp);
	piped = 0;
	head_lst = pipeline->cmd_lst;
	aux_fd[0] = -1;
	aux_fd[1] = -1;
	while (pipeline->cmd_lst)
	{
		acmd = pipeline->cmd_lst->content;
		if (!piped)
			fd[0] = dup(fd_std_tmp[0]);
		piped = 0;
		set_redir_fd(acmd->redir_lst, aux_fd);
		printf("%d %d\n", aux_fd[0], aux_fd[1]);
	/*	redir_aux = acmd->redir_lst;
		while (redir_aux)
		{
			printf("Entra\n");
			aredir = redir_aux->content;
			if (aredir->type == LESS)
				aux_fd[0] = open(aredir->file, O_RDONLY);
			if (aredir->type == GREAT)
				aux_fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			else if (aredir->type == DGREAT)
				aux_fd[1] = open(aredir->file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			redir_aux = redir_aux->next;
		}*/
		//ft_lstclear(&acmd->redir_lst, free_redir);
		if (aux_fd[0] >= 0)
		{
			dup2(aux_fd[0], fd[0]);
			close(aux_fd[0]);
		}
		set_std_fd(fd, 0);
		if (pipeline->cmd_lst->next)
		{
			pipe(fd);
			piped = 1;
		}
		set_std_fd(fd, 1);
		if (!piped)
			fd[1] = dup(fd_std_tmp[1]);
		if (aux_fd[1] >= 0)
		{
			dup2(aux_fd[1], fd[1]);
			close(aux_fd[1]);
		}
		set_std_fd(fd, 1);
		if (acmd)
			find_command(acmd, prompt);
		printf("Entra\n");
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
	ft_lstclear(&head_lst, free_command);
	reset_std_fd(fd_std_tmp);
}


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
