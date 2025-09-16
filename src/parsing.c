/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 11:25:36 by mzimeris         ###   ########.fr       */
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

int	process_map_line(char *line, t_data *data)
{
	static int	map_line_count = 0;
	int			len;

	if (!line || !data)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	map_line_count++;
	data->map->height = map_line_count;
	if (len > data->map->width)
		data->map->width = len;
	return (1);
}

// parsing des textures et couleurs a affiner.
int	process_line(char *line, t_data *data)
{
	if (!line || !data)
		return (0);
	if (ft_strlen(line) == 0)
		return (1);
	if (ft_strncmp(line, "N", 1) == 0)
		data->textures->north_texture = ft_my_strdup(data->allocator, line + 3);
	else if (ft_strncmp(line, "S", 1) == 0)
		data->textures->south_texture = ft_my_strdup(data->allocator, line + 3);
	else if (ft_strncmp(line, "W", 1) == 0)
		data->textures->west_texture = ft_my_strdup(data->allocator, line + 3);
	else if (ft_strncmp(line, "E", 1) == 0)
		data->textures->east_texture = ft_my_strdup(data->allocator, line + 3);
	else if (ft_strncmp(line, "F", 1) == 0)
		data->textures->floor_color = extract_rgb(data,
				data->textures->floor_color, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		data->textures->ceiling_color = extract_rgb(data,
				data->textures->ceiling_color, line);
	else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
		process_map_line(line, data);
	return (1);
}

int	parse_file(char *filename, t_data **data)
{
	int		fd;
	char	*line;

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
	if ((*data)->map->height > 0 && (*data)->map->width > 0)
		if (!parse_map(filename, data))
			return (0);
	if (!init_player(*data))
		return (0);
	return (1);
}
