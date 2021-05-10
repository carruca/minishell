/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:00:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/26 15:12:04 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

typedef struct s_shell
{
	char	*prompt;
	t_list	*pipeline_lst;
	int		status;
}			t_shell;

void	print_prompt(char *prompt);
char	*read_command_line(void);
void	read_eval_print_loop(t_shell *sh);

#endif
