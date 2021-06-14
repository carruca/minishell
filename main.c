/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 20:51:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/10 17:00:29 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(char *prompt)
{
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("$ ", 1);
}

char	*get_prompt(char *arg1)
{
	char *pos;

	pos = ft_strrchr(arg1, '/');
	if (!pos)
		return (arg1);
	return (pos + 1);
}

void	read_eval_print_loop(t_shell *sh)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = NULL;
		print_prompt(sh->prompt);
		tcsetattr(1, TCSAFLUSH, &sh->my_term);
		tputs(tgetstr("ks", 0), 1, ft_putchar);
		read_cmdline(&cmd_line, &sh->cap);
		tcsetattr(1, TCSANOW, &sh->term);
		sh->pipeline_lst = parser(cmd_line, sh->prompt);
		if (sh->pipeline_lst)
			executer(sh);
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

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	ft_bzero(&sh, sizeof(t_shell));
	sh.prompt = get_prompt(argv[0]);
	init_envlst(&sh, env);
	if (!sh.env_lst)
		return (1);
	init_environ(&sh.cap);
	if (tgetent(0, get_env("TERM", sh.env_lst)) == -1)
	{
		print_error(&sh, "env", "TERM not set", 1);
		return (sh.status);
	}
	tcgetattr(1, &sh.term);
	init_keyboard(&sh);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	if (argc == 1)
		read_eval_print_loop(&sh);
	tcsetattr(1, TCSANOW, &sh.term);
	return (sh.status);
}
