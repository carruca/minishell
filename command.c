/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:11:16 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/26 18:36:41 by tsierra-         ###   ########.fr       */
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

char	*get_exe_path(char *name)
{
	char		*env_path;
	char		*dir_path;
	char		*exe_path;
	struct stat	buf;

	if (ft_strchr(name, '/'))
	{
		if (stat(name, &buf) == -1)
			return (NULL);
		return (ft_strdup(name));
	}
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

void	print_command_error(char *cmd, char *prompt)
{
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}
