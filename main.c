#include "minishell.h"
#include "parser.h"
#include "executer.h"

void	print_prompt(char *prompt)
{
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("$ ", 1);
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

	cmd_line = NULL;
	while (1)
	{
		print_prompt(sh->prompt);
		cmd_line = read_command_line();
		sh->pipeline_lst = parser(cmd_line, sh->prompt);
		if (sh->pipeline_lst)
			executer(sh);
		if (!ft_strcmp(cmd_line, "exit"))
		{
			free(cmd_line);
			system("leaks minishell");
			exit(EXIT_SUCCESS);
		}
		free(cmd_line);
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

int	main(int argc, char **argv)
{
	t_shell	sh;

//	signal(SIGINT, sig_handler);
//	signal(SIGQUIT, sig_handler);
	ft_bzero(&sh, sizeof(sh));
	sh.prompt = ft_strrchr(argv[0], '/') + 1;
	if (argc == 1)
		read_eval_print_loop(&sh);
	return (0);
}
