/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:45:06 by maadam            #+#    #+#             */
/*   Updated: 2020/06/12 16:45:06 by maadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_free_mem(char **line, char **ostatok)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	if (*ostatok)
	{
		free(*ostatok);
		*ostatok = NULL;
	}
	return (-1);
}

int		ft_read(char **line, char *buff, char **ostatok)
{
	char	*new_l_ptr;
	int		flag;

	new_l_ptr = NULL;
	flag = 0;
	if ((new_l_ptr = ft_strchr(buff, '\n')))
	{
		*new_l_ptr = '\0';
		flag = 1;
		if ((*ostatok = ft_strdup(++new_l_ptr)) == NULL)
			return (ft_free_mem(line, ostatok));
	}
	return (flag);
}

int		ft_ostatok(char **line, char **ostatok, char **new_l_ptr)
{
	if ((*new_l_ptr = ft_strchr(*ostatok, '\n')))
	{
		**new_l_ptr = '\0';
		if ((*line = ft_strdup(*ostatok)) == NULL)
			return (-1);
		(*new_l_ptr)++;
		*ostatok = ft_strcpy(*ostatok, *new_l_ptr);
	}
	else
	{
		if ((*line = ft_strdup(*ostatok)) == NULL)
			return (-1);
		free(*ostatok);
		*ostatok = NULL;
	}
	return (0);
}

int		ft_test_ostatok(char **line, char **ostatok)
{
	char	*new_l_ptr;
	int		flag;

	new_l_ptr = NULL;
	flag = 0;
	if (*ostatok)
		flag = ft_ostatok(line, ostatok, &new_l_ptr);
	else
	{
		if ((*line = ft_strdup("")) == NULL)
			return (-1);
	}
	if (flag < 0)
		return (-1);
	return ((new_l_ptr == NULL) ? 0 : 1);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static	char	*ostatok;
	int				read_len;
	char			*prev_line;
	int				flag;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	read_len = 0;
	if ((flag = ft_test_ostatok(line, &ostatok)) < 0)
		return (ft_free_mem(line, &ostatok));
	while (flag == 0 && (read_len = read(fd, &buff, BUFFER_SIZE)))
	{
		if (read_len < 0)
			return (ft_free_mem(line, &ostatok));
		buff[read_len] = '\0';
		flag = ft_read(line, buff, &ostatok);
		if (flag < 0)
			return (ft_free_mem(line, &ostatok));
		prev_line = *line;
		if ((*line = ft_strjoin(*line, buff)) == NULL)
			return (ft_free_mem(line, &ostatok));
		free(prev_line);
	}
	return ((read_len || flag) ? 1 : 0);
}
