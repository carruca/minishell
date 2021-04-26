/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:37:06 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/26 15:08:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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

t_list	*parser(char *input, char *prompt);
t_list	*parse_pipeline(t_list **tkn_lst, char *prompt);
t_pip	*new_pipeline(t_list **tkn_lst, char *prompt);
t_list	*parse_command(t_list **tkn_lst, char *prompt);
t_cmd	*new_simple_command(t_list **tkn_lst, char *prompt);
void	parse_args(t_list **tkn_lst, t_list **args_lst);
int		parse_redir(t_list **tkn_lst, t_cmd *cmd, int id, char *prompt);
t_redir	*new_redirection(t_list **tkn_lst, int type, char *prompt);
int		parse_pipe(t_list **tkn_lst, t_cmd *cmd, int *pipe, char *prompt);
void	print_syntax_error(char *token, t_list **tkn_lst, char *prompt);
void	free_redir(void *redir);
void	free_command(void *cmd);
void	free_pipeline(void *pipeline);

#endif
