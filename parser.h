/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:37:06 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/29 17:16:43 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"
# include "token.h"
# include <stdio.h>

typedef struct s_redirection
{
	char	*file;
	int		type;
}			t_redir;

typedef struct s_command
{
	t_list	*args_lst;
	t_list	*redir_lst;
	int		pipe;
}			t_cmd;

typedef struct s_pipeline
{
	t_list	*cmd_lst;
}			t_pip;

t_list	*parser(char *input);
t_list	*parse_pipeline(t_list **tkn_lst);

#endif
