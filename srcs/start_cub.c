/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:03:55 by maadam            #+#    #+#             */
/*   Updated: 2020/10/06 18:03:55 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			my_mlx_pixel_put(t_win *img, int x, int y, int color)
{
	char	*dst;

	dst = img->adrr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

static	void	ft_draw_f_c(t_all *s_all, int h)
{
	int		x;
	int		y;
	int		c;

	y = 0;
	c = h == s_all->win.h ? s_all->tex.f : s_all->tex.c;
	while (y < h)
	{
		x = 0;
		while (x < s_all->win.w)
		{
			my_mlx_pixel_put(&(*s_all).win, x, y, c);
			x++;
		}
		y++;
	}
}

void			ft_raycast(t_all *s_all)
{
	int		x;

	ft_draw_f_c(s_all, s_all->win.h);
	ft_draw_f_c(s_all, s_all->win.h / 2);
	x = -1;
	while (++x < s_all->win.w)
	{
		s_all->dir.map_x = (int)s_all->plr.x;
		s_all->dir.map_y = (int)s_all->plr.y;
		ft_ray_dir_n_dist_xy(s_all, x);
		ft_ray_step(s_all);
		ft_rays_steps_to_wall(s_all, x);
		ft_wall_heigh_n_tex_choise(s_all, x);
		ft_put_tex_on_wall(s_all, x);
	}
	if (s_all->spr.spr)
		ft_sprites(s_all);
	if (!s_all->ss_flag)
		mlx_put_image_to_window(s_all->win.mlx, s_all->win.wind,
								s_all->win.img, 0, 0);
	else
		ft_screenshot(s_all);
}

static	int		ft_mem_for_rays_n_sprites(t_all *s_all)
{
	if (!(s_all->dir.perp_wall_dist = (float *)malloc(sizeof(float *)
			* s_all->win.w)))
		return (-30);
	if (s_all->spr.spr)
	{
		if (!(s_all->spr.y = (float *)malloc(sizeof(float *)
				* s_all->spr.spr)))
			return (-29);
		if (!(s_all->spr.x = (float *)malloc(sizeof(float *)
				* s_all->spr.spr)))
			return (-29);
		if (!(s_all->spr.dist = (float *)malloc(sizeof(float *)
				* s_all->spr.spr)))
			return (-29);
		ft_check_sprites_pos(s_all);
	}
	return (0);
}

int				ft_start_cub(t_all *s_all)
{
	if ((s_all->err.err_num = ft_mem_for_rays_n_sprites(s_all)) < 0)
		return (s_all->err.err_num);
	if (!s_all->ss_flag)
	{
		if (!(s_all->win.wind = mlx_new_window(s_all->win.mlx, s_all->win.w,
												s_all->win.h, "CUB3D")))
			return (-28);
	}
	if (!(s_all->win.img = mlx_new_image(s_all->win.mlx, s_all->win.w,
											s_all->win.h)))
		return (-28);
	if (!(s_all->win.adrr = mlx_get_data_addr(s_all->win.img, &s_all->win.bpp,
											&s_all->win.len, &s_all->win.end)))
		return (-28);
	mlx_do_sync(s_all->win.mlx);
	ft_raycast(s_all);
	mlx_hook(s_all->win.wind, 2, 1L << 0, ft_key_check, s_all);
	mlx_hook(s_all->win.wind, 17, 1L << 17, ft_close_prog, s_all);
	mlx_loop(s_all->win.mlx);
	return (0);
}
