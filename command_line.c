#include "minishell.h"
#include <termios.h>
#include <curses.h>
#include <sys/ioctl.h>

void	init_aux(t_cap *cap)
{
	ft_bzero(cap->cmd_buff, sizeof(cap->cmd_buff));
	cap->str = '\0';
	cap->index_ch = 0;
	cap->check_esc = 0;
	cap->cmd_cursor = cap->cmd_buff;
	cap->len_cursor = 0;
}

void	control_key(t_cap *cap)
{
	if (cap->str == '\e')
		cap->check_esc = TRUE;
	if (!ft_strcmp(cap->ch, tgetstr("ku", 0)))
		cap->index_ch = cap_key_up(cap);
	else if (!ft_strcmp(cap->ch, tgetstr("kd", 0)))
		cap->index_ch = cap_key_down(cap);
	else if (!ft_strcmp(cap->ch, tgetstr("kr", 0)))
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
	}
	else if (!ft_strcmp(cap->ch, tgetstr("kl", 0)))
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
	}
	else if (ft_isprint(cap->str) && cap->check_esc == FALSE)
		cap->index_ch = cap_key_printable(cap);
	else if (cap->check_esc == TRUE && cap->ch[2] != '\0')
	{
		cap->index_ch = 0;
		ft_bzero(cap->ch, sizeof(cap->ch));
		cap->check_esc = FALSE;
	}
}

void	sig_ctrl_c(void)
{
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("minishell$ ", 1);
}

int	control_cap(t_cap *cap)
{
	if (cap->str == CTRL_C)
	{
		sig_ctrl_c();
		tputs(save_cursor, 1, ft_putchar);
		return (1);
	}
	else if (cap->str == CTRL_D)
	{
		if (*cap->cmd_buff)
		{
			cap->index_ch = 0;
			ft_bzero(cap->ch, sizeof(cap->ch));
			return (2);
		}
		else
			return (3);
	}
	else if (cap->str == CTRL_4)
		return (4);
	else if (cap->str == DL_KEY)
	{
		cap_delete_char(cap);
		return (5);
	}
	return (0);
}

int	capture_key(char **cmd, t_cap *cap, t_line *line)
{
	int	check_ctrl;

	check_ctrl = control_cap(cap);
	if (check_ctrl)
	{
		if (check_ctrl == 3)
		{
			printf("\n");
			*cmd = "exit";
			return (1);
		}
	}
	else if (cap->str == NL_KEY)
	{
		line = cap->cli->content;
		if (*cap->cmd_buff || line->origin_line)
		{
			*cmd = next_line_key(cap);
			return (3);
		}
		*cmd = "";
		printf("\n");
		return (4);
	}
	return (0);
}

int	*read_cmdline(char **cmd, t_cap *cap)
{
	t_line	line;
	int		check_capkey;

	init_aux(cap);
	tputs(save_cursor, 1, ft_putchar);
	while (cap->str != NL_KEY)
	{
		read(0, &cap->str, 1);
		check_capkey = capture_key(&*cmd, cap, &line);
		if (check_capkey)
		{
			if (check_capkey == 1 || check_capkey == 3)
				break ;
		}
		else if (cap->str != DL_KEY && cap->str != NL_KEY && cap->str != TAB
			&& cap->str != CTRL_D)
		{
			cap->ch[cap->index_ch++] = cap->str;
			control_key(cap);
		}
	}
	return (0);
}
