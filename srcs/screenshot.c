/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:44:28 by maadam            #+#    #+#             */
/*   Updated: 2020/09/15 21:44:28 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		my_mlx_get_color(t_win *win, int x, int y)
{
	char	*dst;

	dst = win->adrr + (y * win->len + x * (win->bpp / 8));
	return (*(unsigned int*)dst);
}

static void		ft_make_ss(t_all *s_all, int fd, int res)
{
	int		color;
	int		x;
	int		y;

	color = 0;
	y = s_all->win.h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < res)
		{
			color = my_mlx_get_color(&s_all->win, x, y);
			write(fd, &color, 3);
			x++;
		}
		y--;
	}
}

static void		ft_header(unsigned char *header, int size, t_all *all, int res)
{
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)size;
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	header[18] = (unsigned char)res;
	header[19] = (unsigned char)(res >> 8);
	header[20] = (unsigned char)(res >> 16);
	header[21] = (unsigned char)(res >> 24);
	header[22] = (unsigned char)all->win.h;
	header[23] = (unsigned char)(all->win.h >> 8);
	header[24] = (unsigned char)(all->win.h >> 16);
	header[25] = (unsigned char)(all->win.h >> 24);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
}

void			ft_screenshot(t_all *s_all)
{
	int				i;
	int				fd;
	int				res;
	int				size;
	unsigned char	header[54];

	res = s_all->win.w;
	if (s_all->win.w % 4)
		res = s_all->win.w - (s_all->win.w % 4);
	size = res * s_all->win.w + 54;
	i = 0;
	if ((fd = open("./cub3D.bmp", O_RDWR | O_CREAT, 0666)) < 0)
		ft_putstr("ERROR: Errors when creating a screenshot file");
	while (i < 54)
		header[i++] = (unsigned char)0;
	ft_header(header, size, s_all, res);
	write(fd, header, 54);
	ft_make_ss(s_all, fd, res);
	close(fd);
	mlx_destroy_image(s_all->win.mlx, s_all->win.img);
	ft_close_prog(s_all);
}

/*
** По умолчанию fopen() использует для creat коды доступа accessmode \
**												равные 0666 (rwrw-rw-)
** BITMAPFILEHEADER — 14-байтная структура, \
**							которая располагается в самом начале файла
** BITMAPINFOHEADER - 40 бвйт / Содержит ширину, высоту и битность растра, \
**		а также формат пикселей, информацию о цветовой таблице и разрешении.
*/
