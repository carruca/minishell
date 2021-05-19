#include "minishell.h"

int	cap_key_printable(t_env *_env)
{
	t_line	*line;
	char	*tmp;

	tmp = NULL;
	line = NULL;
	line = _env->cli->content;
	write(1, &_env->str, 1);
	if (_env->cli_bufflen < 2048)
	{
		*_env->cmd_cursor = *_env->ch;
		_env->cli_bufflen++;
		_env->len_cursor++;
		_env->cmd_cursor++;
		*_env->cmd_cursor = '\0';
	}
	if (*(line->origin_line) || !_env->cli->prev)
	{
		if (line->clone_line != NULL)
			tmp = line->clone_line;
		line->clone_line = ft_strdup(_env->cmd_buff);
		if (tmp)
			free(tmp);
	}
	ft_bzero(_env->ch, sizeof(_env->ch));
	_env->check_esc = 0;
	return (0);
}
