/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:51:35 by tsierra-          #+#    #+#             */
/*   Updated: 2021/04/26 13:40:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# include "lexer.h"
# include <stdio.h>

# define WORD	0x0001
# define LESS	0x0002
# define GREAT	0x0004
# define DGREAT	0x0008
# define PIPE	0x0010
# define SCOLON	0x0020
# define EXPAN	0x0040
# define TOGET	0x0080

typedef struct s_token
{
	char	*token;
	int		identifier;
}			t_token;

t_token		*new_token(char *str);
int			id_token(char *str);
void		free_token(void *tkn);
void		print_token(void *tkn);
void		del_current_token(t_list **tkn_lst);

#endif
