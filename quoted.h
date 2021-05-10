/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:06:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/07 13:14:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTED_H
# define QUOTED_H

int	args_have_quotes(t_list *lst);
int	redir_file_have_quotes(char **str, char *prompt);

#endif
