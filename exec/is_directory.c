/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:07:36 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 21:08:12 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_directory(char *path)
{
	DIR	*dirp;

	dirp = opendir(path);
	if (!dirp)
		return (0);
	closedir(dirp);
	return (1);
}
