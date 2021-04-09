/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:00:45 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/09 17:27:57 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "lexer.h"
# include "token.h"
# include "parser.h"
# include "executer.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

typedef struct s_all
{
	char	*prompt;
	t_list	*tree_lst;
}			t_all;

void	print_prompt();
char	*read_command_line();
void	read_eval_print_loop();

#endif
