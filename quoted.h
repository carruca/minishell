/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:06:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/03 16:00:57 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTED_H
# define QUOTED_H

void	args_have_quotes(t_list *lst);
void	redir_have_quotes(t_list *lst);
void	redir_file_have_quotes(char **str);

#endif
