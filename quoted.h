/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:06:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/10 16:10:11 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTED_H
# define QUOTED_H

# include "minishell.h"

void	args_have_quotes(t_list *lst, t_shell *sh);
int		redir_file_have_quotes(char **str, t_shell *sh);

#endif
