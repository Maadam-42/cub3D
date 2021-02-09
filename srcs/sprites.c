/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:07:40 by maadam            #+#    #+#             */
/*   Updated: 2020/10/29 16:07:40 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	ft_get_color_and_pixel_put(t_all *s_all)
{
	int			y;
	int			d;
	uint32_t	color;

	y = s_all->spr.draw_start_y;
	while (y < s_all->spr.draw_end_y)
	{
		d = (y) * 256 - s_all->win.h * 128 + s_all->spr.sprite_h * 128;
		s_all->spr.tex_y = ((d * s_all->tex.sp.h) / s_all->spr.sprite_h) / 256;
		color = *(int*)(s_all->tex.sp.addr + ((s_all->spr.tex_x +
			(s_all->spr.tex_y * s_all->tex.sp.w)) * (s_all->tex.sp.bpp / 8)));
		if (color & 0x00FFFFFF)
			my_mlx_pixel_put(&(*s_all).win, s_all->spr.stripe, y, color);
		y++;
	}
}

static	void	ft_draw_sprite(t_all *s_all)
{
	s_all->spr.stripe = s_all->spr.draw_start_x;
	while (s_all->spr.stripe < s_all->spr.draw_end_x)
	{
		s_all->spr.tex_x = (int)((256 * (s_all->spr.stripe - \
			(-s_all->spr.sprite_w / 2 + s_all->spr.sprite_screen_x)) * \
			s_all->tex.sp.w / s_all->spr.sprite_w) / 256);
		if (s_all->spr.transform_y > 0 && s_all->spr.stripe >= 0 && \
			s_all->spr.stripe < s_all->win.w && s_all->spr.transform_y \
			< s_all->dir.perp_wall_dist[s_all->spr.stripe])
			ft_get_color_and_pixel_put(s_all);
		s_all->spr.stripe += 1;
	}
}

static	void	ft_sprite_size_on_screen(t_all *s_all)
{
	s_all->spr.sprite_h = abs((int)(s_all->win.h / s_all->spr.transform_y));
	s_all->spr.draw_start_y = -s_all->spr.sprite_h / 2 + s_all->win.h / 2;
	if (s_all->spr.draw_start_y < 0)
		s_all->spr.draw_start_y = 0;
	s_all->spr.draw_end_y = s_all->spr.sprite_h / 2 + s_all->win.h / 2;
	if (s_all->spr.draw_end_y >= s_all->win.h)
		s_all->spr.draw_end_y = s_all->win.h;
	s_all->spr.sprite_w = abs((int)(s_all->win.h / s_all->spr.transform_y));
	s_all->spr.draw_start_x = -s_all->spr.sprite_w / 2 + \
		s_all->spr.sprite_screen_x;
	if (s_all->spr.draw_start_x < 0)
		s_all->spr.draw_start_x = 0;
	s_all->spr.draw_end_x = s_all->spr.sprite_w / 2 + \
		s_all->spr.sprite_screen_x;
	if (s_all->spr.draw_end_x > s_all->win.w)
		s_all->spr.draw_end_x = s_all->win.w;
}

static	void	ft_sprite_depth(t_all *s_all, int i)
{
	s_all->spr.sprite_x = s_all->spr.x[i] - s_all->plr.x;
	s_all->spr.sprite_y = s_all->spr.y[i] - s_all->plr.y;
	s_all->spr.inv_det = 1.0 / (s_all->dir.plane_x * s_all->dir.y - \
		s_all->dir.x * s_all->dir.plane_y);
	s_all->spr.transform_x = s_all->spr.inv_det * (s_all->dir.y * \
		s_all->spr.sprite_x - s_all->dir.x * s_all->spr.sprite_y);
	s_all->spr.transform_y = s_all->spr.inv_det * (-s_all->dir.plane_y * \
		s_all->spr.sprite_x + s_all->dir.plane_x * s_all->spr.sprite_y);
	s_all->spr.sprite_screen_x = (int)((s_all->win.w / 2) * \
		(1 + s_all->spr.transform_x / s_all->spr.transform_y));
}

void			ft_sprites(t_all *s_all)
{
	int		i;

	i = -1;
	while (++i < s_all->spr.spr)
	{
		s_all->spr.dist[i] = ((s_all->plr.x - s_all->spr.x[i]) * \
		(s_all->plr.x - s_all->spr.x[i]) + (s_all->plr.y - s_all->spr.y[i] * \
		(s_all->plr.y - s_all->spr.y[i])));
	}
	ft_sort_sprites(s_all);
	i = -1;
	while (++i <= s_all->spr.spr)
	{
		ft_sprite_depth(s_all, i);
		ft_sprite_size_on_screen(s_all);
		ft_draw_sprite(s_all);
	}
}
