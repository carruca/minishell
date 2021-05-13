#include "minishell.h"

char	*next_line_key(t_env *_env)
{
	t_line	*line;

	line = _env->cli->content;
	if (*_env->cmd_buff)
	{
		create_node(_env);
		_env->cli_bufflen = 0;
		while (_env->cli->prev)
		{
			line = _env->cli->content;
			_env->cli = _env->cli->prev;
		}
	}	
	write(1, "\n", 1);
	if (_env->cli->next->content)
	{
		line = _env->cli->next->content;
		free(line->clone_line);
		return (line->origin_line);
	}
	else
		return (NULL);
}
