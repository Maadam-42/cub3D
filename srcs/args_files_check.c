/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_files_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:50:23 by maadam            #+#    #+#             */
/*   Updated: 2020/09/22 18:50:23 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_check_space(char *line, int *i)
{
	int		k;

	(*i)++;
	k = (*i);
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n' ||
			line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r')
		(*i)++;
	if ((*i) - k)
		return (k);
	return (0);
}

int		ft_ss_check(char const *arg, char const *ss)
{
	int		i;

	if (!arg || !ss)
		return (-1);
	i = 0;
	while (arg[i] == ss[i])
	{
		if (arg[i] == '\0' && ss[i] == '\0')
			return (1);
		i++;
	}
	return (ft_print_err(-17));
}

int		ft_arg_fileex_check(char const *arg, char c)
{
	int	i;

	i = ft_strlen(arg);
	if (c == 'a')
	{
		if (arg[i - 1] == 'b' && arg[i - 2] == 'u' && arg[i - 3] == 'c' &&
			arg[i - 4] == '.')
			return (1);
		return (ft_print_err(-16));
	}
	else if (c == 'f')
	{
		if (arg[i - 1] == 'm' && arg[i - 2] == 'p' && arg[i - 3] == 'x' &&
			arg[i - 4] == '.')
			return (1);
		return (ft_print_err(-5));
	}
	return (0);
}
