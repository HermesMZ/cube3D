/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:11:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 18:59:06 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Fonction pour allouer le grid de la carte
int	allocate_map_grid(t_data *data)
{
	int	i;

	if (data->map->height <= 0 || data->map->width <= 0)
		return (0);
	data->map->grid = ft_my_malloc(data->allocator,
			sizeof(char *) * (data->map->height + 1));
	if (!data->map->grid)
		return (0);
	i = 0;
	while (i < data->map->height)
	{
		data->map->grid[i] = ft_my_malloc(data->allocator,
				data->map->width + 1);
		if (!data->map->grid[i])
			return (0);
		ft_memset(data->map->grid[i], ' ', data->map->width);
		data->map->grid[i][data->map->width] = '\0';
		i++;
	}
	data->map->grid[data->map->height] = NULL;
	return (1);
}

char	*skip_to_map_start(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !is_map_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	fill_map_grid_data(t_data *data, int fd, char *first_line)
{
	char	*line;
	int		row;
	int		j;
	int		len;

	line = first_line;
	row = 0;
	while (line && is_map_line(line) && row < data->map->height)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		j = 0;
		while (j < len && j < data->map->width)
		{
			data->map->grid[row][j] = line[j];
			j++;
		}
		free(line);
		row++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}

int	find_map_start_and_fill(t_data *data, int fd)
{
	char	*first_line;

	first_line = skip_to_map_start(fd);
	if (!first_line)
		return (0);
	return (fill_map_grid_data(data, fd, first_line));
}

int	parse_map_from_file(t_data **data, char *filename)
{
	int		fd;

	if (!allocate_map_grid(*data))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!find_map_start_and_fill(*data, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
