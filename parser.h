/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:37:06 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/24 16:38:54 by tsierra-         ###   ########.fr       */
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
	int		redirection;
}			t_redir;

typedef struct s_command
{
	t_list	*args;
	int		pipe;
	t_redir	*redir;
}			t_cmd;

typedef struct s_pipeline
{
	t_list	*cmd_lst;
}			t_pip;

t_list	*parser(char *input);
t_list	*parse_pipeline(t_list **tkn_lst);

#endif
