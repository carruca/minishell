#include "minishell.h"

int	cap_key_printable(t_env *lst_env)
{
	t_line	*line;

	line = lst_env->cli->content;
	write(1, &lst_env->str, 1);
	if (lst_env->cli_bufflen < 2048)
	{
		*lst_env->cmd_cursor = *lst_env->ch;
		lst_env->cli_bufflen++;
		lst_env->len_cursor++;
		lst_env->cmd_cursor++;
		*lst_env->cmd_cursor = '\0';
	}
	if (*(line->origin_line))
		line->clone_line = ft_strdup(lst_env->cmd_buff);
	ft_bzero(lst_env->ch, sizeof(lst_env->ch));
	lst_env->check_esc = 0;
	return (0);
}
