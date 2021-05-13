#include "minishell.h"
#include <termios.h>
#include <curses.h>
#include <sys/ioctl.h>

void	init_aux(t_env *lst_env)
{
	ft_bzero(lst_env->cmd_buff, sizeof(lst_env->cmd_buff));
	lst_env->str = '\0';
	lst_env->index_ch = 0;
	lst_env->check_esc = 0;
	lst_env->cmd_cursor = lst_env->cmd_buff;
	lst_env->len_cursor = 0;
}

void	control_key(t_env *_env)
{
	if (_env->str == '\e')
		_env->check_esc = TRUE;
	if (!ft_strcmp(_env->ch, tgetstr("ku", 0)))
		_env->index_ch = cap_key_up(_env);
	else if (!ft_strcmp(_env->ch, tgetstr("kd", 0)))
		_env->index_ch = cap_key_down(_env);
	else if (!ft_strcmp(_env->ch, tgetstr("kr", 0)))
		_env->index_ch = cap_key_right(_env);
	else if (!ft_strcmp(_env->ch, tgetstr("kl", 0)))
		_env->index_ch = cap_key_left(_env);
	else if (ft_isprint(_env->str) && _env->check_esc == FALSE)
		_env->index_ch = cap_key_printable(_env);	
}

int	*read_cmdline(char **cmd, t_env *_env)
{
	init_aux(_env);
	tputs(save_cursor, 1, ft_putchar);
	while (_env->str != NL_KEY)
	{
		read(0, &_env->str, 1);
		if (_env->str != DL_KEY && _env->str != NL_KEY)
		{
			_env->ch[_env->index_ch++] = _env->str;
			control_key(_env);
		}
		else if (_env->str == DL_KEY)
			cap_delete_char(_env);
		else if (_env->str == NL_KEY)
		{
			if (*_env->cmd_buff)
			{
				*cmd = next_line_key(_env);
				break ;
			}
			*cmd = "";
			printf("\n");
		}
	}
	return (0);
}
