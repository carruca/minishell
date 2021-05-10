/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:11:16 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/10 16:19:47 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"

extern char	**environ;

int	search_directory(char *path, char *name)
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

char	*get_exe_path(char *name, t_shell *sh)
{
	t_path		path;
	struct stat	buf;

	ft_bzero(&path, sizeof(t_path));
	if (ft_strchr(name, '/'))
	{
		if (stat(name, &buf) == -1)
			return (NULL);
		return (ft_strdup(name));
	}
	sh->status = sh->status;
	path.env = ft_strdup(getenv("PATH"));
	path.dir = ft_strtok(path.env, ":");
	while (path.dir != NULL)
	{
		if (search_directory(path.dir, name))
		{
			path.exe = ft_strjoin_btwchar(path.dir, name, '/');
			free(path.env);
			return (path.exe);
		}
		path.dir = ft_strtok(NULL, ":");
	}
	free(path.env);
	return (NULL);
}

int	executer_command(char *path, char **argv)
{
	int		status;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
		return (0);
	else if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, argv, environ);
		exit(0);
	}
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
/*
void	print_command_error(char *cmd, char *prompt, int *status)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	*status = 126;
}*/
