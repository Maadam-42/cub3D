/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:22:20 by maadam            #+#    #+#             */
/*   Updated: 2020/09/29 11:22:20 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			ft_correct_map_w(int x, char **map)
{
	int		y;
	char	*tmp;

	y = -1;
	while (map[++y])
	{
		while ((int)(ft_strlen(map[y])) < x)
		{
			tmp = map[y];
			map[y] = ft_strjoin(map[y], " ");
			free(tmp);
		}
	}
}

void			ft_get_position(t_all *s_all, char c)
{
	if (c == 'W')
	{
		s_all->dir.x = -1;
		s_all->dir.plane_y = -tan(FOV / 2 * M_PI / 180);
	}
	else if (c == 'E')
	{
		s_all->dir.x = 1;
		s_all->dir.plane_y = tan(FOV / 2 * M_PI / 180);
	}
	else if (c == 'N')
	{
		s_all->dir.y = -1;
		s_all->dir.plane_x = tan(FOV / 2 * M_PI / 180);
	}
	else if (c == 'S')
	{
		s_all->dir.y = 1;
		s_all->dir.plane_x = -tan(FOV / 2 * M_PI / 180);
	}
}

static	int		ft_line_len(char *line, t_all *s_all)
{
	int		i;
	int		check_len;

	i = 0;
	check_len = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '1' || line[i] == '0')
			check_len++;
		else if (line[i] == '2' && (s_all->spr.spr += 1))
			check_len++;
		else if (line[i] == 'W' || line[i] == 'E' || line[i] == 'S' ||
				line[i] == 'N')
		{
			check_len++;
			ft_get_position(s_all, line[i]);
			s_all->plr.check_pos++;
			s_all->plr.y = (s_all->map.y + 0.5);
			s_all->plr.x = (i + 0.5);
		}
		i++;
	}
	if (i != check_len)
		return (s_all->err.err_line = -1);
	return (check_len);
}

static	char	*ft_check_copy_line(char *line, int *i, t_all *s_all)
{
	int		k;
	int		len;
	char	*tmp_mass;

	k = 0;
	if ((len = ft_line_len(line, s_all)) < 0)
		return (NULL);
	if (!(tmp_mass = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (line[*i])
	{
		tmp_mass[k] = line[*i];
		k++;
		(*i)++;
	}
	tmp_mass[k] = '\0';
	s_all->map.x = s_all->map.x < k ? k : s_all->map.x;
	s_all->map_flag++;
	return (tmp_mass);
}

int				ft_pars_map(char *line, int *i, t_all *s_all)
{
	int		y;
	int		k;
	char	**tmp_map;

	k = 0;
	y = -1;
	ft_isspace(line, &k);
	if (line[k] == '\0')
		return (-27);
	if (!(tmp_map = malloc(sizeof(char *) * (s_all->map.y + 2))))
		return (-10);
	while (++y < s_all->map.y)
		tmp_map[y] = s_all->map.map_mass[y];
	if (!(tmp_map[y] = ft_check_copy_line(line, i, s_all)))
		return (s_all->err.err_line == -1 ? -32 : -10);
	tmp_map[y + 1] = NULL;
	if (s_all->map.y > 0)
		free(s_all->map.map_mass);
	s_all->map.map_mass = tmp_map;
	s_all->map.map_mass[y + 1] = NULL;
	s_all->map.y++;
	return (0);
}
