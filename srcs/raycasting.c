/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:03:48 by maadam            #+#    #+#             */
/*   Updated: 2020/11/15 14:03:48 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_put_tex_on_wall(t_all *s_all, int x)
{
	int		y;

	s_all->dir.wall_x = s_all->dir.side_is_xy < 2 ? s_all->plr.y +
		s_all->dir.perp_wall_dist[x] * s_all->dir.ray_dir_y : s_all->plr.x +
		s_all->dir.perp_wall_dist[x] * s_all->dir.ray_dir_x;
	s_all->dir.wall_x -= (int)(s_all->dir.wall_x);
	s_all->dir.tex_x = (int)(s_all->dir.wall_x * (float)(s_all->dir.tex.w));
	if (s_all->dir.side_is_xy == 0 || s_all->dir.side_is_xy == 3)
		s_all->dir.tex_x = (int)((float)s_all->dir.tex.w - s_all->dir.wall_x *
			(float)s_all->dir.tex.w - 1);
	s_all->dir.step = 1.0 * s_all->dir.tex.h / s_all->dir.line_h;
	s_all->dir.tex_pos = (s_all->dir.draw_start - s_all->win.h / 2 +
		s_all->dir.line_h / 2) * s_all->dir.step;
	y = s_all->dir.draw_start;
	while (y <= s_all->dir.draw_end)
	{
		s_all->dir.tex_y = (int)s_all->dir.tex_pos;
		s_all->dir.color = *(int *)(s_all->dir.tex.addr + ((s_all->dir.tex_x +
		(s_all->dir.tex_y * s_all->dir.tex.w)) * (s_all->dir.tex.bpp / 8)));
		s_all->dir.tex_pos += s_all->dir.step;
		my_mlx_pixel_put(&(*s_all).win, x, y++, s_all->dir.color);
	}
}

void	ft_wall_heigh_n_tex_choise(t_all *s_all, int x)
{
	s_all->dir.line_h = (int)(s_all->win.h / s_all->dir.perp_wall_dist[x]);
	s_all->dir.draw_start = -s_all->dir.line_h / 2 + s_all->win.h / 2;
	if (s_all->dir.draw_start < 0)
		s_all->dir.draw_start = 0;
	s_all->dir.draw_end = s_all->dir.line_h / 2 + s_all->win.h / 2;
	if (s_all->dir.draw_end >= s_all->win.h)
		s_all->dir.draw_end = s_all->win.h - 1;
	if (s_all->dir.side_is_xy == 0)
		s_all->dir.tex = s_all->tex.w;
	else if (s_all->dir.side_is_xy == 1)
		s_all->dir.tex = s_all->tex.e;
	else if (s_all->dir.side_is_xy == 2)
		s_all->dir.tex = s_all->tex.n;
	else if (s_all->dir.side_is_xy == 3)
		s_all->dir.tex = s_all->tex.s;
}

void	ft_rays_steps_to_wall(t_all *s_all, int x)
{
	s_all->dir.hit = 0;
	while (s_all->dir.hit == 0)
	{
		if (s_all->dir.side_dist_x < s_all->dir.side_dist_y)
		{
			s_all->dir.side_dist_x += s_all->dir.delta_dist_x;
			s_all->dir.map_x += s_all->dir.step_x;
			s_all->dir.side_is_xy = (s_all->dir.ray_dir_x < 0) ? 0 : 1;
		}
		else
		{
			s_all->dir.side_dist_y += s_all->dir.delta_dist_y;
			s_all->dir.map_y += s_all->dir.step_y;
			s_all->dir.side_is_xy = (s_all->dir.ray_dir_y < 0) ? 2 : 3;
		}
		if (s_all->map.map_mass[s_all->dir.map_y][s_all->dir.map_x] == '1')
			s_all->dir.hit = 1;
	}
	if (s_all->dir.side_is_xy < 2)
		s_all->dir.perp_wall_dist[x] = (s_all->dir.map_x - s_all->plr.x +
			(1 - s_all->dir.step_x) / 2) / s_all->dir.ray_dir_x;
	else
		s_all->dir.perp_wall_dist[x] = (s_all->dir.map_y - s_all->plr.y +
			(1 - s_all->dir.step_y) / 2) / s_all->dir.ray_dir_y;
}

void	ft_ray_step(t_all *s_all)
{
	if (s_all->dir.ray_dir_x < 0)
	{
		s_all->dir.step_x = -1;
		s_all->dir.side_dist_x =
			(s_all->plr.x - s_all->dir.map_x) * s_all->dir.delta_dist_x;
	}
	else
	{
		s_all->dir.step_x = 1;
		s_all->dir.side_dist_x =
			(s_all->dir.map_x + 1.0 - s_all->plr.x) * s_all->dir.delta_dist_x;
	}
	if (s_all->dir.ray_dir_y < 0)
	{
		s_all->dir.step_y = -1;
		s_all->dir.side_dist_y =
			(s_all->plr.y - s_all->dir.map_y) * s_all->dir.delta_dist_y;
	}
	else
	{
		s_all->dir.step_y = 1;
		s_all->dir.side_dist_y =
			(s_all->dir.map_y + 1.0 - s_all->plr.y) * s_all->dir.delta_dist_y;
	}
}

void	ft_ray_dir_n_dist_xy(t_all *s_all, int x)
{
	s_all->dir.camera_x = 2 * x / (float)s_all->win.w - 1;
	s_all->dir.ray_dir_x =
		s_all->dir.x + s_all->dir.plane_x * s_all->dir.camera_x;
	s_all->dir.ray_dir_y =
		s_all->dir.y + s_all->dir.plane_y * s_all->dir.camera_x;
	if (!s_all->dir.ray_dir_y)
		s_all->dir.delta_dist_x = 0;
	else
		s_all->dir.delta_dist_x = !s_all->dir.ray_dir_x ?
			1 : fabs(1 / s_all->dir.ray_dir_x);
	if (!s_all->dir.ray_dir_x)
		s_all->dir.delta_dist_y = 0;
	else
		s_all->dir.delta_dist_y = !s_all->dir.ray_dir_y ?
			1 : fabs(1 / s_all->dir.ray_dir_y);
}
