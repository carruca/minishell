#include "minishell.h"

int	cap_key_printable(t_cap *cap)
{
	t_line	*line;
	char	*tmp;

	tmp = NULL;
	line = NULL;
	line = cap->cli->content;
	write(1, &cap->str, 1);
	if (cap->cli_bufflen < 2048)
	{
		*cap->cmd_cursor = *cap->ch;
		cap->cli_bufflen++;
		cap->len_cursor++;
		cap->cmd_cursor++;
		*cap->cmd_cursor = '\0';
	}
	if (*(line->origin_line) || !cap->cli->prev)
	{
		if (line->clone_line != NULL)
			tmp = line->clone_line;
		line->clone_line = ft_strdup(cap->cmd_buff);
		if (tmp)
			free(tmp);
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
