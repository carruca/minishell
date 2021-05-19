#include "minishell.h"

void	print_prompt(char *prompt)
{
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("$ ", 1);
}

void	init_environ(t_env *_env)
{
	create_empty_node(_env);
}

void	free_lista(t_env *_env)
{
	t_lista *node;

	while (_env->cli)
	{
		node = _env->cli;
		free_node(_env->cli);
		_env->cli = _env->cli->next;
		free(node);
	}
}

void	init_keyboard(t_shell *sh)
{
	sh->my_term = sh->term;
	sh->my_term.c_lflag &= ~(ECHO | ICANON);
	sh->my_term.c_cc[VMIN] = 1;
	sh->my_term.c_cc[VTIME] = 0;
	tcsetattr(1, TCSAFLUSH, &sh->my_term);
	tputs(tgetstr("ks", 0), 1, ft_putchar);
}

char	*read_command_line(void)
{
	char	*line;

	line = NULL;
	if (get_next_line(0, &line) < 0)
		ft_putstr_fd("Error\n", 2);
	return (line);
}

void	read_eval_print_loop(t_shell *sh)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = NULL;
		print_prompt(sh->prompt);
		read_cmdline(&cmd_line, &sh->_env);
//		cmd_line = read_command_line();
		sh->pipeline_lst = parser(cmd_line, sh->prompt);
		if (sh->pipeline_lst)
			executer(sh);
//		free(cmd_line);
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(sig, 1);
	}
	ft_putchar_fd('\n', 1);
}

int	main(int argc, char **argv, char **environ)
{
	t_shell	sh;

	ft_bzero(&sh, sizeof(sh));
	init_environ(&sh._env);
	tgetent(0, getenv("TERM"));
	tcgetattr(1, &sh.term);
	init_keyboard(&sh);
	capture(&sh._env, environ);
	set_shelllvl(&sh._env);
//	signal(SIGINT, sig_handler);
//	signal(SIGQUIT, sig_handler);
	sh.prompt = ft_strrchr(argv[0], '/') + 1;
	if (argc == 1)
		read_eval_print_loop(&sh);
	tcsetattr(1, TCSANOW, &sh.term);
	return (0);
}
