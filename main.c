#include "minishell.h"

void	print_prompt(char *prompt)
{
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("$ ", 1);
}

char	*read_command_line()
{
	char *line;

	line = NULL;
	if (get_next_line(0, &line) < 0)
		ft_putstr_fd("Error\n", 2);
	return (line);
}

void	read_eval_print_loop(t_all *all)
{
	char	*cmd_line;
	
	cmd_line = NULL;
	while (1)
	{
		print_prompt(all->prompt);
		cmd_line = read_command_line();
		all->tree_lst = parser(cmd_line, all->prompt);
		if (all->tree_lst)
			executer(all->tree_lst, all->prompt);
		if (!ft_strcmp(cmd_line, "exit"))
		{
			free(cmd_line);
			system("leaks minishell");
			exit(EXIT_SUCCESS);
		}
		free(cmd_line);
	//	system("leaks minishell");
	}
}

int	main(int argc, char **argv)
{
	t_all	all;

	ft_bzero(&all, sizeof(all));
	all.prompt = ft_strrchr(argv[0], '/') + 1;
	if (argc == 1)
		read_eval_print_loop(&all);
	return (0);
}
