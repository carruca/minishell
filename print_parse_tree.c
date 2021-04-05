/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parse_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:25:17 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/05 17:53:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_redir(void *redir)
{
	 t_redir	*tmp;

	 tmp = redir;
	 printf("--------*redir file = %s\n", tmp->file);
	 printf("--------*redir type = %d\n", tmp->type);
}

void	print_arg(void *arg)
{
	char	*tmp;

	tmp = arg;
	printf("--------*arg = %s\n", tmp);
}

void	print_command(void *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp)
	{
		printf("-----\\\n------*Command:\n");
		printf("-------\\\n");
		ft_lstiter(tmp->args_lst, print_arg);
		ft_lstiter(tmp->redir_lst, print_redir);
		if (tmp->pipe)
			printf("--------*pipe = %d\n", tmp->pipe);
	}
}

void	print_pipeline(void *pipeline)
{
	t_pip	*tmp;

	tmp = pipeline;
	if (tmp)
	{
		printf("#################################\n----*Pipeline:\n");
		ft_lstiter(tmp->cmd_lst, print_command);
	}
}

void	print_parse_tree(t_list *pipeline_lst)
{
	if (pipeline_lst)
	{
		printf("#################################\n");
		ft_lstiter(pipeline_lst, print_pipeline);
		printf("#################################\n");
		printf("#################################\n");
	}
}
