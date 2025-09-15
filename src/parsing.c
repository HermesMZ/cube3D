/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/15 18:20:49 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

t_color	*extract_rgb(t_data *data, t_color *color, char *line)
{
	if (!line || !color)
		return (ft_my_free(data->allocator, color), NULL);
	color->r = 0;
	color->g = 0;
	color->b = 0;
	while (*line && !ft_isdigit(*line))
		line++;
	while (*line && ft_isdigit(*line))
		color->r = color->r * 10 + (*line++ - '0');
	while (*line && !ft_isdigit(*line))
		line++;
	while (*line && ft_isdigit(*line))
		color->g = color->g * 10 + (*line++ - '0');
	while (*line && !ft_isdigit(*line))
		line++;
	while (*line && ft_isdigit(*line))
		color->b = color->b * 10 + (*line++ - '0');
	return (color);
}

// Allocate memory for the map grid
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
				sizeof(char) * (data->map->width + 1));
		if (!data->map->grid[i])
			return (0);
		ft_memset(data->map->grid[i], ' ', data->map->width);
		data->map->grid[i][data->map->width] = '\0';
		i++;
	}
	data->map->grid[data->map->height] = NULL;
	return (1);
}

// stockage de la carte dans une matrice 2D
int	process_map_line(char *line, t_data *data)
{
	static int	i = 0;
	int			j;
	int			len;

	if (!line || !data || !data->map->grid)
		return (0);
	len = ft_strlen(line);
	if (i >= data->map->height)
		return (0);
	j = 0;
	while (j < len && j < data->map->width)
	{
		data->map->grid[i][j] = line[j];
		j++;
	}
	i++;
	return (1);
}

// parsing des textures et couleurs a affiner.
int	process_line(char *line, t_data *data)
{
	if (!line || !data)
		return (0);
	if (ft_strlen(line) == 0)
		return (1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->textures->north_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->textures->south_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->textures->west_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->textures->east_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		data->textures->floor_color = extract_rgb(data,
				data->textures->floor_color, line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->textures->ceiling_color = extract_rgb(data,
				data->textures->ceiling_color, line);
	else if (line[0] == '1' || line[0] == '0')
		process_map_line(line, data);
	return (1);
}

int	parse_file(char *filename, t_data **data)
{
	int		fd;
	char	*line;

	if (!count_map_lines(filename, *data))
		return (0);
	if (!allocate_map_grid(*data))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(line, *data))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
