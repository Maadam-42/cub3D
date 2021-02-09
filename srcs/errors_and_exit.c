/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 22:24:31 by maadam            #+#    #+#             */
/*   Updated: 2020/09/18 22:24:31 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_clean_map(t_all *s_all)
{
	int i;

	i = -1;
	if (s_all->map.map_mass)
	{
		while (s_all->map.map_mass[++i])
			free(s_all->map.map_mass[i]);
	}
}

int		ft_close_prog(t_all *s_all)
{
	if (s_all->win.wind)
		mlx_destroy_window(s_all->win.mlx, s_all->win.wind);
	if (s_all->tex.w.addr)
		mlx_destroy_image(s_all->win.mlx, s_all->tex.w.img);
	if (s_all->tex.e.addr)
		mlx_destroy_image(s_all->win.mlx, s_all->tex.e.img);
	if (s_all->tex.s.addr)
		mlx_destroy_image(s_all->win.mlx, s_all->tex.s.img);
	if (s_all->tex.n.addr)
		mlx_destroy_image(s_all->win.mlx, s_all->tex.n.img);
	if (s_all->tex.sp.addr)
		mlx_destroy_image(s_all->win.mlx, s_all->tex.sp.img);
	if (s_all->win.img && !s_all->ss_flag)
		mlx_destroy_image(s_all->win.mlx, s_all->win.img);
	if (s_all->win.mlx)
		free(s_all->win.mlx);
	s_all->spr.y ? free(s_all->spr.y) : 0;
	s_all->spr.x ? free(s_all->spr.x) : 0;
	s_all->spr.dist ? free(s_all->spr.dist) : 0;
	s_all->dir.perp_wall_dist ? free(s_all->dir.perp_wall_dist) : 0;
	s_all->map.map_mass ? free(s_all->map.map_mass) : 0;
	exit(0);
	return (0);
}

void	ft_print_err_2(int err)
{
	err == -14 ? ft_putstr("ERROR: Check if texture is not dublicate\n") : 0;
	err == -15 ? ft_putstr("ERROR: Check spaces after file extension\n") : 0;
	err == -16 ? ft_putstr("ERROR: Check maps name\n") : 0;
	err == -17 ? ft_putstr("ERROR: Check if third argument is correct\n") : 0;
	err == -18 ? ft_putstr("ERROR: No resolution in config file\n") : 0;
	err == -19 ? ft_putstr("ERROR: No EA texture in config file\n") : 0;
	err == -20 ? ft_putstr("ERROR: No NO texture in config file\n") : 0;
	err == -21 ? ft_putstr("ERROR: No SO texture in config file\n") : 0;
	err == -22 ? ft_putstr("ERROR: No WE texture in config file\n") : 0;
	err == -23 ? ft_putstr("ERROR: Check if ceilings and floors values is \
correct and not dublicated\n") : 0;
	err == -24 ? ft_putstr("ERROR: Map is not correct (maybe there are holes \
somewhere..?)\n") : 0;
	err == -25 ? ft_putstr("ERROR: Map is not correct (maybe there is empty \
line..?)\n") : 0;
	err == -26 ? ft_putstr("ERROR: No player on the map\n") : 0;
	err == -27 ? ft_putstr("ERROR: Empty line with extra spaces\n") : 0;
	err == -28 ? ft_putstr("ERROR: mlx fail\n") : 0;
	err == -29 ? ft_putstr("ERROR: malloc fail (arrays for sprites \
(coordinates and distance)\n") : 0;
	err == -30 ? ft_putstr("ERROR: malloc fail \
(array for rays distance)\n") : 0;
	err == -31 ? ft_putstr("ERROR: No S texture in config file\n") : 0;
	err == -32 ? ft_putstr("ERROR: Not valid symbols in the map\n") : 0;
}

int		ft_print_err(int err)
{
	err == -42 ? ft_putstr("ERROR: FD fails\n") : 0;
	err == -1 ? ft_putstr("Parsing stoped (get_next_line part)\n") : 0;
	err == -2 ? ft_putstr("ERROR: Check if screen resolution \
is not dublicate\n") : 0;
	err == -3 ? ft_putstr("ERROR: Check if screen resolution is correct \
(maybe there are extra spaces at the end..?)\n") : 0;
	err == -4 ? ft_putstr("ERROR: malloc fail (path to texture file)\n") : 0;
	err == -5 ? ft_putstr("ERROR: Check texture file extension\n") : 0;
	err == -6 ? ft_putstr("ERROR: Texture file read fail (fd error)\n") : 0;
	err == -7 ? ft_putstr("ERROR: Texture file read fail \
(img = mlx error)\n") : 0;
	err == -8 ? ft_putstr("ERROR: Check floors color value (maybe there are \
extra spaces at the end..?)\n") : 0;
	err == -9 ? ft_putstr("ERROR: Check ceilings color value (maybe there are \
extra spaces at the end..?)\n") : 0;
	err == -10 ? ft_putstr("ERROR: malloc fail (building map part)\n") : 0;
	err == -11 ? ft_putstr("ERROR: More than one player on the map\n") : 0;
	err == -12 ? ft_putstr("ERROR: Check the line (invalid line or maybe there \
are extra spaces at the end..?) \n") : 0;
	err == -13 ? ft_putstr("ERROR: Check if сeilings or floors color is \
not dublicate\n") : 0;
	if (err < -13)
		ft_print_err_2(err);
	return (-1);
}
