/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:48:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/07 20:48:36 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include <stdio.h>
#include <dirent.h>

extern char **environ;

char	**lst_to_argv(t_list *lst)
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

int		search_dir(char *path, char *name)
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

char	*get_path(char *dir_path, char *name)
{
	char	*path;
	int		name_len;
	int		dir_len;

	dir_len = ft_strlen(dir_path);
	name_len = ft_strlen(name);
	path = malloc(sizeof(char) * (dir_len + name_len + 2));
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir_path, dir_len + 1);
	path[dir_len] = '/';
	ft_strlcpy(path + dir_len + 1, name, name_len + 1);
	path[dir_len + name_len + 1] = '\0';
	return (path);
}

char	*find_path(char *name)
{
	char	*path_dir;
	char	*path_env;
	char	*path;

	if (!ft_strchr(name, '/'))
	{
		path_env = ft_strdup(getenv("PATH"));
		path_dir = ft_strtok(path_env, ":");
		while (path_dir != NULL)
		{
			if (search_dir(path_dir, name))
			{
				path = get_path(path_dir, name);
				free(path_env);
				return (path);
			}
			path_dir = ft_strtok(NULL, ":");
		}
		free(path_env);
	}
	else
		return (name);
	return (NULL);
}

void	executer_command(t_cmd *cmd)
{
	int		status;
	pid_t	child_pid;
	char	**argv;
	char	*path;

	child_pid = fork();
	if (child_pid < 0)
		return ;
	else if (child_pid == 0)
	{
		argv = lst_to_argv(cmd->args_lst);
		path = find_path(argv[0]);
		execve(path, argv, environ);
		free(path);
		ft_free_tab(argv);
		exit(0);
	}
	waitpid(child_pid, &status, 0);
}

void	executer_pipeline(t_pip *pipeline)
{
	t_list	*head;
	t_cmd	*acmd;

	head = pipeline->cmd_lst;
	while (pipeline->cmd_lst)
	{
		acmd = pipeline->cmd_lst->content;
		if (acmd)
		{
		//	printf("cmd\n");
			executer_command(acmd);
		}
		pipeline->cmd_lst = pipeline->cmd_lst->next;
	}
	ft_lstclear(&head, free_command);
}

void	executer(t_list *pipeline_lst)
{
	t_list	*head;
	t_pip	*apipeline;

	head = pipeline_lst;
	while (pipeline_lst)
	{
		apipeline = pipeline_lst->content;
		if (apipeline)
		{
		//	printf("pipeline\n");
			executer_pipeline(apipeline);
		}
		pipeline_lst = pipeline_lst->next;
	}
	ft_lstclear(&head, free_pipeline);
}
