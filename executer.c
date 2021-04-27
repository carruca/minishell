/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:48:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/27 14:24:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "parser.h"
#include "token.h"
/*
char	**ft_lsttoa(t_list *lst)
{
	char	**new;
	int		counter;
	int		i;
	
	counter = ft_lstsize(lst);
	new = ft_calloc(counter + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < counter)
	{
		new[i] = ft_strdup((char *)lst->content);
		if (!new[i])
		{
			ft_free_tab(new);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}
*/
/*
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
*/
/*
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
*/
/*
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
*/
void	find_command(t_cmd *cmd, char *prompt)
{
	char	**argv;
	char	*path;

	argv = ft_lsttoa(cmd->args_lst);
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
/*
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

void	set_fd(int *fd, int id)
{
	dup2(fd[id], id);
	close(fd[id]);
}
*/

void	print_file_error(char *file, char *prompt)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	set_redir_fd(t_list *redir_lst, int	*fd, char *prompt)
{
	t_redir		*aredir;

	ft_bzero(fd, sizeof(fd));
	while (redir_lst)
	{
		aredir = redir_lst->content;
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
/*
void	set_std_fd(int *fd, int *redir_fd, int *std_fd, int *piped, int id)
{
	if (*piped == 0)
		fd[id] = dup(std_fd[id]);
	if (redir_fd[id] > 2)
	{
		dup2(redir_fd[id], fd[id]);
		close(redir_fd[id]);
	}
	set_fd(fd, id);
}

void	set_pipe(int *fd, int *piped)
{
	pipe(fd);
	set_fd(fd, 1);
	*piped = 1;
}
*/

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
