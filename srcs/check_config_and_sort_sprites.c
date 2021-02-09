/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_and_sort_sprites.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:36:34 by maadam            #+#    #+#             */
/*   Updated: 2020/10/06 15:36:34 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_sort_sprites(t_all *s_all)
{
	int		i;
	int		k;
	float	tmp;

	i = 1;
	while (i < s_all->spr.spr)
	{
		k = i;
		while (k > 0 && s_all->spr.dist[k - 1] < s_all->spr.dist[k])
		{
			tmp = s_all->spr.dist[k - 1];
			s_all->spr.dist[k - 1] = s_all->spr.dist[k];
			s_all->spr.dist[k] = tmp;
			tmp = s_all->spr.y[k - 1];
			s_all->spr.y[k - 1] = s_all->spr.y[k];
			s_all->spr.y[k] = tmp;
			tmp = s_all->spr.x[k - 1];
			s_all->spr.x[k - 1] = s_all->spr.x[k];
			s_all->spr.x[k] = tmp;
			k--;
		}
		i++;
	}
}

void	ft_check_sprites_pos(t_all *s_all)
{
	int		yy;
	int		xx;
	int		i;

	i = 0;
	yy = 0;
	while (s_all->map.map_mass[yy])
	{
		xx = 0;
		while (s_all->map.map_mass[yy][xx])
		{
			if (s_all->map.map_mass[yy][xx] == '2')
			{
				s_all->spr.y[i] = (float)(yy + 0.5);
				s_all->spr.x[i++] = (float)(xx + 0.5);
			}
			xx++;
		}
		yy++;
	}
}

int		ft_check_map(t_all s_all, char **map)
{
	int		x;
	int		y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] != '\0')
		{
			if (map[y][x] == '0' || map[y][x] == 'E' || map[y][x] == 'W' ||
				map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == '2')
			{
				if ((x == 0 || x == (int)(ft_strlen(map[y]) - 1)) ||
						(y == 0 || y == s_all.map.y - 1))
					return (-1);
				if ((x > 0 && map[y][x - 1] == ' ') ||
						(x != (int)(ft_strlen(map[y])) && map[y][x + 1] == ' '))
					return (-1);
				if ((y > 0 && map[y - 1][x] == ' ') ||
						(y != s_all.map.y - 1 && map[y + 1][x] == ' '))
					return (-1);
			}
		}
	}
	return (0);
}

int		ft_check_config(t_all s_all)
{
	if (s_all.gnl_check != -1)
	{
		if (s_all.win.h == 0 || s_all.win.w == 0)
			return (-18);
		if (s_all.tex.e.fl == 0)
			return (-19);
		if (s_all.tex.n.fl == 0)
			return (-20);
		if (s_all.tex.s.fl == 0)
			return (-21);
		if (s_all.tex.w.fl == 0)
			return (-22);
		if (s_all.tex.sp.fl == 0)
			return (-31);
		if (s_all.tex.c_fl == 0 || s_all.tex.c_fl > 1 || s_all.tex.f_fl == 0
			|| s_all.tex.f_fl > 1)
			return (-23);
		if (s_all.plr.check_pos == 0)
			return (-26);
		if (s_all.plr.check_pos > 1)
			return (-11);
		if (ft_check_map(s_all, s_all.map.map_mass) < 0)
			return (-24);
	}
	return (0);
}
