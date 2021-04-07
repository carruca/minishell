/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:48:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/06 17:57:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include <stdio.h>
#include <unistd.h>

extern char **environ;

char	**lst_to_argv(t_list *lst)
{
	char	**vector;
	int		count;
	int		i;
	
	count = ft_lstsize(lst);
	vector = ft_calloc(count + 1, sizeof(char *));
	if (!vector)
		return (NULL);
	i = 0;
	while (i < count)
	{
		vector[i] = ft_strdup((char *)lst->content);
		if (!vector[i])
		{
			ft_free_tab(vector);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	vector[i] = NULL;
	return (vector);
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

char	*find_path(char *cmd)
{
	char	*path;

	path = NULL;
	(void)cmd;
	return (NULL);
}

void	executer_command(t_cmd *cmd)
{
	char	**argv;

	argv = lst_to_argv(cmd->args_lst);
	print_argv(argv);
	execve("/bin/", argv, environ);
	ft_free_tab(argv);

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
			printf("cmd\n");
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
			printf("pipeline\n");
			executer_pipeline(apipeline);
		}
		pipeline_lst = pipeline_lst->next;
	}
	ft_lstclear(&head, free_pipeline);
}
