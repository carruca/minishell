#include "minishell.h"

int	cap_key_left(t_env *_env)
{	
	if (_env->len_cursor)
	{
		tputs(cursor_left, 1, ft_putchar);
		_env->len_cursor--;
	}
	ft_bzero(_env->ch, sizeof(_env->ch));
	_env->check_esc = 0;
	return (0);
}
