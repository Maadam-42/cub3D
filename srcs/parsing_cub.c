/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:50:27 by maadam            #+#    #+#             */
/*   Updated: 2020/09/18 16:50:27 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	int		ft_pars_c_f_color(char *line, int *i, t_all *s_all, char c)
{
	int r;
	int g;
	int b;

	if ((c == 'c' && s_all->tex.c != 0) || (c == 'f' && s_all->tex.f != 0))
		return (-13);
	(*i)++;
	ft_isspace(line, i);
	r = ft_atoi(line, i);
	if (line[*i] != ',')
		return (-9);
	(*i)++;
	g = ft_atoi(line, i);
	if (line[*i] != ',')
		return (-9);
	(*i)++;
	b = ft_atoi(line, i);
	if (r < 0 || r > 255 || b < 0 || b > 255 || g < 0 || g > 255
			|| line[*i] != '\0')
		return (-9);
	if (c == 'c')
		s_all->tex.c = 65536 * r + 256 * g + b;
	if (c == 'f')
		s_all->tex.f = 65536 * r + 256 * g + b;
	return (0);
}

static	int		ft_pars_text(char *line, int *i, t_all *s_all, t_tex_img *tex)
{
	char	*f_name;
	int		k;

	if (tex->fl > 1)
		return (-14);
	(*i) += 2;
	ft_isspace(line, i);
	if (!(f_name = ft_strdup(&line[*i])))
		return (-4);
	if ((k = ft_arg_fileex_check(f_name, 'f')) == -1)
		return (-15);
	if ((k = open(f_name, O_RDONLY)) == -1)
		return (-6);
	if (!(tex->img = mlx_xpm_file_to_image(s_all->win.mlx, f_name,
											&tex->w, &tex->h)))
		return (-7);
	free(f_name);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->len, &tex->end);
	return (0);
}

static	int		ft_pars_screen_resolution(char *line, int *i, t_all *s_all)
{
	int		s_x;
	int		s_y;

	if (s_all->win.w != 0 || s_all->win.h != 0)
		return (-2);
	(*i)++;
	s_all->win.w = ft_atoi(line, i);
	s_all->win.h = ft_atoi(line, i);
	mlx_get_screen_size(s_all->win.mlx, &s_x, &s_y);
	s_all->win.w = s_all->win.w > s_x ? s_x : s_all->win.w;
	s_all->win.h = s_all->win.h > s_y ? s_y : s_all->win.h;
	if (s_all->win.w < 100 && s_all->win.w > 0)
		s_all->win.w = 100;
	if (s_all->win.h < 100 && s_all->win.h > 0)
		s_all->win.h = 100;
	if (s_all->win.w <= 0 || s_all->win.h <= 0 || line[*i] != '\0')
		return (-3);
	return (0);
}

static	void	ft_pars_cub_2(char *line, int i, t_all *s_all)
{
	if ((line[i] == '1' || line[i] == ' ' || s_all->map_flag) &&
		line[i] != '\0')
		s_all->err.err_num = ft_pars_map(line, &i, s_all);
	else if (line[i] != '\0' && !s_all->err.err_line && !s_all->err.err_num)
		s_all->err.err_num = -12;
}

int				ft_pars_cub(char *line, t_all *s_all)
{
	int i;

	i = 0;
	if (line[i] == '\0' && s_all->map_flag)
		s_all->err.err_num = -25;
	if (line[i] == 'R' && line[i + 1] == ' ')
		s_all->err.err_num = ft_pars_screen_resolution(line, &i, s_all);
	else if ((line[i] == 'N' && line[i + 1] == 'O') && (s_all->tex.n.fl += 1))
		s_all->err.err_num = ft_pars_text(line, &i, s_all, &s_all->tex.n);
	else if ((line[i] == 'S' && line[i + 1] == 'O') && (s_all->tex.s.fl += 1))
		s_all->err.err_num = ft_pars_text(line, &i, s_all, &s_all->tex.s);
	else if ((line[i] == 'W' && line[i + 1] == 'E') && (s_all->tex.w.fl += 1))
		s_all->err.err_num = ft_pars_text(line, &i, s_all, &s_all->tex.w);
	else if ((line[i] == 'E' && line[i + 1] == 'A') && (s_all->tex.e.fl += 1))
		s_all->err.err_num = ft_pars_text(line, &i, s_all, &s_all->tex.e);
	else if ((line[i] == 'S' && line[i + 1] == ' ') && (s_all->tex.sp.fl += 1))
		s_all->err.err_num = ft_pars_text(line, &i, s_all, &s_all->tex.sp);
	else if ((line[i] == 'C' && line[i + 1] == ' ') && (s_all->tex.c_fl += 1))
		s_all->err.err_num = ft_pars_c_f_color(line, &i, s_all, 'c');
	else if ((line[i] == 'F' && line[i + 1] == ' ') && (s_all->tex.f_fl += 1))
		s_all->err.err_num = ft_pars_c_f_color(line, &i, s_all, 'f');
	else
		ft_pars_cub_2(line, i, s_all);
	return (s_all->err.err_num != 0 ? -1 : 0);
}
