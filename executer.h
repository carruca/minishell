/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:49:33 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/09 17:36:16 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>

void	executer(t_list *pipeline_lst, char *prompt);

#endif
