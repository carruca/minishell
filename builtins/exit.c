/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:08:34 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/28 20:12:51 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_str_longint(const char *str)
{
	size_t	i;
	int		neg;
	double	num;

	i = 0;
	neg = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
		if (num * neg > LONG_MAX)
			return (0);
		if (num * neg < LONG_MIN)
			return (0);
	}
	return (1);
}

int	ft_isneg(const char *s)
{
	if (s[0] == '-' && ft_isdigit(s[1]))
		return (1);
	return (0);
}

int	builtin_exit(t_shell *sh, int argc, char **argv)
{
	ft_putstr_fd(argv[0], 1);
	ft_putstr_fd("\n", 1);
	sh->status = 0;
	if (argc > 1)
	{
		if (!ft_is_str_longint(argv[1])
			|| (!ft_is_str_digit(argv[1]) && !ft_isneg(argv[1])))
			print_builtin_error(sh, argv, "numeric argument required", 255);
		else if (argc > 2)
			print_builtin_error(sh, argv, "too many arguments", 1);
		else
			sh->status = ft_atoi(argv[1]);
	}
	tcsetattr(1, TCSANOW, &sh->term);
	exit(sh->status);
}
