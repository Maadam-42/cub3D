/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:41:52 by maadam            #+#    #+#             */
/*   Updated: 2020/10/14 17:41:52 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	ft_move_f_b(int key, t_all *s_all)
{
	if (key == W)
	{
		if (s_all->map.map_mass[(int)((s_all->plr.y + s_all->dir.y * SP))]\
		[(int)(s_all->plr.x)] != '1' && s_all->map.map_mass[(int)\
		((s_all->plr.y + s_all->dir.y * SP))][(int)(s_all->plr.x)] != '2')
			s_all->plr.y += s_all->dir.y * SP;
		if (s_all->map.map_mass[(int)(s_all->plr.y)][(int)((s_all->plr.x + \
		s_all->dir.x * SP))] != '1' && s_all->map.map_mass[(int)\
		(s_all->plr.y)][(int)((s_all->plr.x + s_all->dir.x * SP))] != '2')
			s_all->plr.x += s_all->dir.x * SP;
	}
	else if (key == S)
	{
		if (s_all->map.map_mass[(int)((s_all->plr.y - s_all->dir.y * SP))]\
		[(int)(s_all->plr.x)] != '1' && s_all->map.map_mass[(int)\
		((s_all->plr.y - s_all->dir.y * SP))][(int)(s_all->plr.x)] != '2')
			s_all->plr.y -= s_all->dir.y * SP;
		if (s_all->map.map_mass[(int)(s_all->plr.y)][(int)((s_all->plr.x - \
		s_all->dir.x * SP))] != '1' && s_all->map.map_mass[(int)\
		(s_all->plr.y)][(int)((s_all->plr.x - s_all->dir.x * SP))] != '2')
			s_all->plr.x -= s_all->dir.x * SP;
	}
}

static	void	ft_move_r_l(int key, t_all *s_all)
{
	if (key == A)
	{
		if (s_all->map.map_mass[(int)s_all->plr.y][(int)(s_all->plr.x - \
		(s_all->dir.plane_x * SP))] != '1' && s_all->map.map_mass[(int)\
		s_all->plr.y][(int)(s_all->plr.x - (s_all->dir.plane_x * SP))] != '2')
			s_all->plr.x -= s_all->dir.plane_x * SP;
		if (s_all->map.map_mass[(int)(s_all->plr.y - (s_all->dir.plane_y * \
		SP))][(int)s_all->plr.x] != '1' && s_all->map.map_mass[(int)\
		(s_all->plr.y - (s_all->dir.plane_y * SP))][(int)s_all->plr.x] != '2')
			s_all->plr.y -= s_all->dir.plane_y * SP;
	}
	else if (key == D)
	{
		if (s_all->map.map_mass[(int)s_all->plr.y][(int)(s_all->plr.x + \
		(s_all->dir.plane_x * SP))] != '1' && s_all->map.map_mass[(int)\
		s_all->plr.y][(int)(s_all->plr.x + (s_all->dir.plane_x * SP))] != '2')
			s_all->plr.x += s_all->dir.plane_x * SP;
		if (s_all->map.map_mass[(int)(s_all->plr.y + (s_all->dir.plane_y * \
		SP))][(int)s_all->plr.x] != '1' && s_all->map.map_mass[(int)\
		(s_all->plr.y + (s_all->dir.plane_y * SP))][(int)s_all->plr.x] != '2')
			s_all->plr.y += s_all->dir.plane_y * SP;
	}
}

static	void	ft_turn_r(int key, t_all *s_all)
{
	float	old_dir_x;
	float	old_plane_x;

	if (key == RIGHT)
	{
		old_dir_x = s_all->dir.x;
		s_all->dir.x = s_all->dir.x * cos(TURN_SP) - s_all->dir.y * \
		sin(TURN_SP);
		s_all->dir.y = old_dir_x * sin(TURN_SP) + s_all->dir.y * \
		cos(TURN_SP);
		old_plane_x = s_all->dir.plane_x;
		s_all->dir.plane_x = s_all->dir.plane_x * cos(TURN_SP) - \
		s_all->dir.plane_y * sin(TURN_SP);
		s_all->dir.plane_y = old_plane_x * sin(TURN_SP) + \
		s_all->dir.plane_y * cos(TURN_SP);
	}
}

static	void	ft_turn_l(int key, t_all *s_all)
{
	float	old_dir_x;
	float	old_plane_x;

	if (key == LEFT)
	{
		old_dir_x = s_all->dir.x;
		s_all->dir.x = s_all->dir.x * cos(-TURN_SP) - s_all->dir.y * \
		sin(-TURN_SP);
		s_all->dir.y = old_dir_x * sin(-TURN_SP) + s_all->dir.y * \
		cos(-TURN_SP);
		old_plane_x = s_all->dir.plane_x;
		s_all->dir.plane_x = s_all->dir.plane_x * cos(-TURN_SP) - \
		s_all->dir.plane_y * sin(-TURN_SP);
		s_all->dir.plane_y = old_plane_x * sin(-TURN_SP) + \
		s_all->dir.plane_y * cos(-TURN_SP);
	}
}

int				ft_key_check(int key, t_all *s_all)
{
	mlx_do_sync(s_all->win.mlx);
	if (key == ESC)
		ft_close_prog(s_all);
	else if (key == W || key == S)
		ft_move_f_b(key, s_all);
	else if (key == A || key == D)
		ft_move_r_l(key, s_all);
	else if (key == RIGHT)
		ft_turn_r(key, s_all);
	else if (key == LEFT)
		ft_turn_l(key, s_all);
	ft_raycast(s_all);
	return (0);
}
