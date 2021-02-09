/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 22:13:33 by maadam            #+#    #+#             */
/*   Updated: 2020/09/18 22:13:33 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_isspace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n' ||
			line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r')
		(*i)++;
}

int		ft_atoi(char *line, int *i)
{
	int		min;
	int		res;
	int		flag;

	min = 1;
	res = 0;
	flag = 0;
	if (line[*i] == '\0')
		return (-1);
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n' ||
			line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r')
		(*i)++;
	if (line[*i] == '-' || line[*i] == '+')
	{
		if (line[*i] == '-')
			min = -1;
		(*i)++;
	}
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		res = res * 10 + (line[*i] - '0');
		(*i)++;
		flag++;
	}
	return (flag > 0 ? res * min : -1);
}

void	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (*str)
		write(1, &(*str++), 1);
}

void	ft_bzero(void *str, size_t n)
{
	char	*ptr;
	size_t	i;

	if (!str)
		return ;
	ptr = str;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
