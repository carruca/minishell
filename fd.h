/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:24:05 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/26 13:24:07 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_H
# define FD_H

# include "executer.h"
# include "minishell.h"

void	set_fd(int *fd, int id);
void	cpy_std_fd(int *fd);
void	reset_std_fd(int *fd);
void	set_std_fd(int *fd, int *redir_fd, int *std_fd, int *piped, int id);
void	set_pipe(int *fd, int *piped);

#endif
