/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:52:22 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/28 19:52:58 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_shell *sh, int argc, char **argv)
{
	int	i;

	sh->status = 0;
	i = 1;
	while (argc > 1 && argv[i])
	{
		if (is_valid_var(argv[i]) != 1)
			print_identifier_error(sh, argv[0], argv[i], 1);
		else
			ft_lstremove_if(&sh->env_lst, argv[i],
				env_name_cmp, free_var);
		i++;
	}
	return (1);
}
