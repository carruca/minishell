#include "minishell.h"

void	print_prompt()
{
	ft_putstr_fd("minishell$ ", 1);
}

char	*read_command_line()
{
	char *line;

	line = NULL;
	if (get_next_line(0, &line) < 0)
		ft_putstr_fd("Error\n", 2);
	return (line);
}

char	*get_delim(char *line)
{
	if (ft_strchr(line, '\"'))
		return ("\"");
	else if (ft_strchr(line, '\''))
		return ("\'");
	else if (ft_strchr(line, ' '))
		return (" ");
	return (" ");
}

void	lexer(char **line)
{
	char	*tok;

	tok = NULL;
	tok = ft_strtok(*line, get_delim(*line));
	while (tok != NULL)
	{
		printf("%s\n", tok);
		tok = ft_strtok(NULL, get_delim(*line));
	}
}

void	parser()
{
	//Token parsing and expansions
}

void	executor()
{
	//I/O redirection and execution
}

void	read_eval_print_loop()
{
	char *cmd_line;

	cmd_line = NULL;
	while (1)
	{
		print_prompt();
		cmd_line = read_command_line();
		printf("%s\n", cmd_line);
		lexer(&cmd_line);
		if (!ft_strcmp(cmd_line, "exit"))
		{
			free(cmd_line);
			system("leaks minishell");
			exit(EXIT_SUCCESS);
		}
		free(cmd_line);
	}
}

int	main()
{
	read_eval_print_loop();
	return (0);
}
