/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:12:40 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/05 17:19:11 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_PARSE_H
# define PRINT_PARSE_H

# include "minishell.h"
# include "lexer.h"
# include <stdio.h>

void	print_parse_tree(t_list *pipeline_lst);
void	print_pipeline(void *pipeline);
void	print_command(void *cmd);
void	print_arg(void *arg);
void	print_redir(void *redir);

#endif
