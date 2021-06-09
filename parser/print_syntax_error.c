/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:52:19 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:53:02 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token, t_list **tkn_lst, char *prompt)
{
	printf("%s: syntax error near unexpected token `%s'\n", prompt, token);
	if (tkn_lst)
		ft_lstclear(tkn_lst, free_token);
}
