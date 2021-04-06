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

void	executor()
{
	//I/O redirection and execution
}

void	read_eval_print_loop(char *prompt)
{
	t_list	*parser_tree;
	char	*cmd_line;
	
	cmd_line = NULL;
	while (1)
	{
		print_prompt(prompt);
		cmd_line = read_command_line();
		parser_tree = parser(cmd_line);
		if (parser_tree)
		{
			printf("parser_tree\n");
			executer(parser_tree);
		}
	//	ft_lstclear(&parser_tree, free_pipeline);
		if (!ft_strcmp(cmd_line, "exit"))
		{
			free(cmd_line);
			system("leaks minishell");
			exit(EXIT_SUCCESS);
		}
		free(cmd_line);
		system("leaks minishell");
	}
}

int	main(int argc, char **argv)
{
	char	*prompt;

	prompt = ft_strrchr(argv[0], '/') + 1;
	if (argc == 1)
	{
		read_eval_print_loop(prompt);
	}
	return (0);
}
