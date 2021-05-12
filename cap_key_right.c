#include "minishell.h"

int	cap_key_right(t_env *_env)
{
	if (_env->cmd_buff[_env->len_cursor])
	{
		tputs(cursor_right, 1, ft_putchar);
		_env->len_cursor++;
	}
	ft_bzero(_env->ch, sizeof(_env->ch));
	_env->check_esc = 0;
	return (0);
}
