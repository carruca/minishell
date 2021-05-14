#include "minishell.h"

void	find_history(t_env *_env)
{
	t_line	*line;

	line = _env->cli->content;
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("ed", 0), 1, ft_putchar);
	tputs(tgetstr("ce", 0), 1, ft_putchar);
	if (line->clone_line && ft_strcmp(line->clone_line, ""))
	{
		ft_strcpy(_env->cmd_buff, line->clone_line);
		_env->cli_bufflen = ft_strlen(line->clone_line);
		_env->len_cursor = _env->cli_bufflen;
		_env->cmd_cursor = _env->cmd_buff + _env->cli_bufflen;
		ft_putstr_fd(line->clone_line, 1);
	}
	else if (line->origin_line)
	{
		ft_strcpy(_env->cmd_buff, line->origin_line);
		_env->cli_bufflen = ft_strlen(line->origin_line);
		_env->len_cursor = _env->cli_bufflen;
		_env->cmd_cursor = _env->cmd_buff + _env->cli_bufflen;
		ft_putstr_fd(line->origin_line, 1);
	}
}
