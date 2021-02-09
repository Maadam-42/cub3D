/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:18:46 by maadam            #+#    #+#             */
/*   Updated: 2020/09/15 13:18:46 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BLACK 0x00000000
# define RED 0x00FF0000

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "minilibx_mms/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4095
# endif

# define FOV 60
# define SP 0.5
# define TURN_SP 0.2

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

typedef	struct		s_win
{
	void			*mlx;
	void			*wind;
	void			*img;
	char			*adrr;
	int				w;
	int				h;
	int				bpp;
	int				len;
	int				end;
}					t_win;

typedef struct		s_plr
{
	int				check_pos;
	float			x;
	float			y;
}					t_plr;

typedef	struct		s_map
{
	int				x;
	int				y;
	char			**map_mass;
}					t_map;

typedef	struct		s_tex_img
{
	int				fl;
	void			*img;
	char			*addr;
	int				bpp;
	int				len;
	int				end;
	int				h;
	int				w;
}					t_tex_img;

typedef	struct		s_tex
{
	unsigned int	c;
	unsigned int	f;
	int				c_fl;
	int				f_fl;
	t_tex_img		w;
	t_tex_img		e;
	t_tex_img		s;
	t_tex_img		n;
	t_tex_img		sp;
}					t_tex;

typedef	struct		s_spr
{
	int				spr;
	float			*y;
	float			*x;
	float			*dist;
	float			sprite_x;
	float			sprite_y;
	float			inv_det;
	float			transform_x;
	float			transform_y;
	int				sprite_screen_x;
	int				sprite_h;
	int				sprite_w;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;;
	int				draw_end_y;
	int				stripe;
	int				tex_x;
	int				tex_y;
}					t_spr;

typedef	struct		s_dir
{
	float			x;
	float			y;
	int				map_x;
	int				map_y;
	float			ray_dir_x;
	float			ray_dir_y;
	float			camera_x;
	float			plane_x;
	float			plane_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			*perp_wall_dist;
	int				side_is_xy;
	float			step_x;
	float			step_y;
	int				hit;
	int				draw_start;
	int				draw_end;
	int				line_h;
	float			wall_x;
	int				tex_x;
	int				tex_y;
	float			tex_pos;
	float			step;
	t_tex_img		tex;
	uint32_t		color;
}					t_dir;

typedef	struct		s_err
{
	int				err_num;
	int				err_line;
}					t_err;

typedef	struct		s_all
{
	t_win			win;
	t_plr			plr;
	t_dir			dir;
	t_err			err;
	t_tex			tex;
	t_spr			spr;
	t_map			map;
	int				map_flag;
	int				gnl_check;
	int				ss_flag;
}					t_all;

/*
** Utils
*/

void				ft_putstr(const char *str);
void				ft_bzero(void *str, size_t n);
void				ft_isspace(char *line, int *i);
int					ft_atoi(char *str, int *i);
int					get_next_line(int fd, char **line);
size_t				ft_strlen(char const *str);
char				*ft_strjoin(char const *str1, char const *str2);
char				*ft_strcpy(char *str1, char const *str2);
char				*ft_strdup(const char *str);
char				*ft_strchr(char const *str, int c);

/*
** Parsing, start and handling cub
*/

int					ft_ss_check(char const *arg, char const *ss);
int					ft_arg_fileex_check(char const *arg, char c);
int					ft_check_space(char *line, int *i);
int					ft_check_config(t_all s_all);
int					ft_pars_cub(char *line, t_all *s_all);
int					ft_pars_map(char *line, int *i, t_all *s_all);
void				ft_check_sprites_pos(t_all *s_all);
void				ft_correct_map_w(int x, char **map);
int					ft_start_cub(t_all *s_all);
int					ft_key_check(int key, t_all *s_all);
void				ft_screenshot(t_all *s_all);
int					ft_print_err(int err);
void				ft_clean_map(t_all *s_all);
int					ft_close_prog(t_all * s_all);

/*
** Raycasting and draw
*/

void				ft_raycast(t_all *s_all);
void				ft_sprites(t_all *s_all);
void				ft_sort_sprites(t_all *s_all);
void				ft_ray_dir_n_dist_xy(t_all *s_all, int x);
void				ft_ray_step(t_all *s_all);
void				ft_rays_steps_to_wall(t_all *s_all, int x);
void				ft_wall_heigh_n_tex_choise(t_all *s_all, int x);
void				ft_put_tex_on_wall(t_all *s_all, int x);
void				my_mlx_pixel_put(t_win *img, int x, int y, int color);

#endif
