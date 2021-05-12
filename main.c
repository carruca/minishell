#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr_fd("minishell$ ", 1);
}

void	init_environ(t_env *_env)
{
	ft_bzero(_env, sizeof(t_env));
	create_empty_node(_env);
}

void	free_lista(t_env *_env)
{
	t_line	*line;

	while (_env->cli->next)
	{
		line = _env->cli->content;
		if (line->origin_line)
			free(line->origin_line);
		if (line->clone_line)
			free(line->clone_line);
		free(line);
		_env->cli = _env->cli->next;
	}
}

void	init_keyboard(struct termios term)
{
	struct termios	aux;

	aux = term;
	aux.c_lflag &= ~(ECHO | ICANON);
	aux.c_cc[VMIN] = 1;
	aux.c_cc[VTIME] = 0;
	tcsetattr(1, TCSAFLUSH, &aux);
	tputs(tgetstr("ks", 0), 1, ft_putchar);
}

int	main(int argc, char *argv[], char **env)
{
	struct termios	term;
	char			*cmd;
	t_env			_env;

	ft_bzero(&term, sizeof(struct termios));
	init_environ(&_env);
	tgetent(0, getenv("TERM"));
	tcgetattr(1, &term);
	init_keyboard(term);
	capture(&_env, env);
	while (TRUE)
	{
		print_prompt();
		cmd = NULL;
		read_cmdline(&cmd, &_env);
		work_to_list(&_env, cmd);
		if (!ft_strcmp(cmd, "exit"))
		{
			free_lista(&_env);
			system("leaks minishell");
			exit(0);
		}
	}
	tcsetattr(1, TCSANOW, &term);
	return (0);
}
