#include "minishell.h"

void	create_empty_node(t_env *_env)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	line->origin_line = ft_strdup("");
	line->clone_line = NULL;
	_env->cli = ft_lst_new_lst(line);
}

void	insert_node_in_list(t_env *_env, t_lista *new)
{
	while (_env->cli->prev)
		_env->cli = _env->cli->prev;
	new->prev = _env->cli;
	if (_env->cli->next)
	{
		new->next = _env->cli->next;
		_env->cli->next->prev = new;
	}
	_env->cli->next = new;
}

void	create_node(t_env *_env)
{
	t_lista	*new;
	t_line	*line;
	t_line	*content;

	content = _env->cli->content;
	line = malloc(sizeof(t_line));
	if (!content->clone_line)
	{
		line->origin_line = ft_strdup(_env->cmd_buff);
		line->clone_line = NULL;
	}
	else
	{
		line->origin_line = ft_strdup(_env->cmd_buff);
		line->clone_line = NULL;
		free(content->clone_line);
		content->clone_line = NULL;
	}
	new = ft_lst_new_lst(line);
	insert_node_in_list(_env, new);
}
