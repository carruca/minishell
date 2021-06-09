/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:51:12 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:51:34 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(char *input, char *prompt)
{
	t_list	*pipeline_lst;
	t_list	*tkn_lst;

	tkn_lst = tokenizer(input);
	if (!tkn_lst)
		return (NULL);
	pipeline_lst = parse_pipeline(&tkn_lst, prompt);
	if (!pipeline_lst)
		return (NULL);
	return (pipeline_lst);
}
