#include "minishell.h"

#include "env.h"

void	error_malloc()
{
	ft_putstr_fd("Error malloc", 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	create_empty_node(t_cap *cap)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		error_malloc();
	line->origin_line = ft_strdup("");
	line->clone_line = NULL;
	cap->cli = ft_lst_new_lst(line);
}

void	insert_node_in_list(t_cap *cap, t_lista *new)
{
	while (cap->cli->prev)
		cap->cli = cap->cli->prev;
	new->prev = cap->cli;
	if (cap->cli->next)
	{
		new->next = cap->cli->next;
		cap->cli->next->prev = new;
	}
	cap->cli->next = new;
}

void	create_node(t_cap *cap)
{
	t_lista	*new;
	t_line	*line;
	t_line	*content;

	content = cap->cli->content;
	line = malloc(sizeof(t_line));
	if (!line)
		error_malloc();
	if (!content->clone_line)
	{
		line->origin_line = ft_strdup(cap->cmd_buff);
		line->clone_line = NULL;
	}
	else
	{
		line->origin_line = ft_strdup(cap->cmd_buff);
		line->clone_line = NULL;
		free(content->clone_line);
		content->clone_line = NULL;
	}
	new = ft_lst_new_lst(line);
	insert_node_in_list(cap, new);
}
