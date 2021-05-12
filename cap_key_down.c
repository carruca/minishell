#include "minishell.h"

int	cap_key_down(t_env *_env)
{
	if (_env->cli->prev)
	{
		_env->cli = _env->cli->prev;
		find_history(_env);
	}
	ft_bzero(_env->ch, sizeof(_env->ch));
	_env->check_esc = 0;
	return (0);
}
