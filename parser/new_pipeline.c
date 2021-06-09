/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:48:22 by tsierra-          #+#    #+#             */
/*   Updated: 2021/06/09 18:49:34 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pip	*new_pipeline(t_list **tkn_lst, char *prompt)
{
	t_pip	*new_pipeline;

	new_pipeline = malloc(sizeof(t_pip));
	if (!new_pipeline)
		return (NULL);
	new_pipeline->cmd_lst = parse_command(tkn_lst, prompt);
	if (!new_pipeline->cmd_lst)
	{
		free_pipeline(new_pipeline);
		return (NULL);
	}
	return (new_pipeline);
}
