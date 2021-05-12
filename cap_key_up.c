#include "minishell.h"

int	cap_key_up(t_env *_env)
{
	if (_env->cli->next)
	{
		_env->cli = _env->cli->next;
		find_history(_env);
	}
	ft_bzero(_env->ch, sizeof(_env->ch));
	_env->check_esc = 0;
	return (0);
}
