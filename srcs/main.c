/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:43:54 by maadam            #+#    #+#             */
/*   Updated: 2020/11/15 22:43:54 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	int		ft_read_cub(char *arg, t_all s_all)
{
	int		fd;
	char	*line;

	line = NULL;
	if ((fd = open(arg, O_RDONLY)) == -1)
		return (ft_print_err(-42));
	while (s_all.gnl_check > 0)
	{
		s_all.gnl_check = get_next_line(fd, &line);
		if (ft_pars_cub(line, &s_all) < 0)
			s_all.gnl_check = -1;
		free(line);
		s_all.gnl_check == -1 ? ft_print_err(-1) : 0;
	}
	close(fd);
	s_all.gnl_check == 0 ? ft_correct_map_w(s_all.map.x, \
	s_all.map.map_mass) : 0;
	if (s_all.gnl_check == -1 || (s_all.err.err_num = ft_check_config(s_all)))
	{
		ft_clean_map(&s_all);
		return (ft_print_err(s_all.err.err_num));
	}
	else
		s_all.err.err_num = ft_start_cub(&s_all);
	return (s_all.err.err_num < 0 ? ft_print_err(s_all.err.err_num) : 0);
}

static	void	ft_struct_init_2(char *arg, t_all s_all)
{
	t_tex	tex;
	t_spr	spr;
	t_dir	dir;
	t_err	err;

	ft_bzero(&dir, sizeof(dir));
	ft_bzero(&tex, sizeof(tex));
	ft_bzero(&spr, sizeof(spr));
	ft_bzero(&err, sizeof(err));
	s_all.dir = dir;
	s_all.tex = tex;
	s_all.spr = spr;
	s_all.err = err;
	s_all.gnl_check = 1;
	s_all.map_flag = 0;
	s_all.win.mlx = mlx_init();
	ft_read_cub(arg, s_all);
}

static	void	ft_struct_init(char *arg, int ss_flag)
{
	t_win	win;
	t_plr	plr;
	t_map	map;
	t_all	s_all;

	ft_bzero(&win, sizeof(win));
	ft_bzero(&plr, sizeof(plr));
	ft_bzero(&map, sizeof(map));
	s_all.map = map;
	s_all.win = win;
	s_all.plr = plr;
	s_all.ss_flag = ss_flag;
	ft_struct_init_2(arg, s_all);
}

int				main(int argc, char **argv)
{
	int	ss_flag;

	ss_flag = 0;
	if (argc == 2)
	{
		if ((ft_arg_fileex_check(argv[1], 'a') > 0) && ss_flag == 0)
			ft_struct_init(argv[1], ss_flag);
	}
	else if (argc == 3)
	{
		if ((ss_flag = ft_ss_check(argv[2], "--save") > 0))
		{
			if (ft_arg_fileex_check(argv[1], 'a'))
				ft_struct_init(argv[1], ss_flag);
		}
	}
	else
		ft_putstr("ERROR: Check that the arguments are correct\n");
	return (0);
}
