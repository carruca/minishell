/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:05:21 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 16:05:32 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_keyboard(t_shell *sh)
{
	sh->my_term = sh->term;
	sh->my_term.c_lflag &= ~(ECHO | ICANON);
	sh->my_term.c_cc[VMIN] = 1;
	sh->my_term.c_cc[VTIME] = 0;
	sh->my_term.c_cc[VINTR] = 0;
	sh->my_term.c_cc[VQUIT] = 0;
	tcsetattr(1, TCSAFLUSH, &sh->my_term);
	tputs(tgetstr("ks", 0), 1, ft_putchar);
}
