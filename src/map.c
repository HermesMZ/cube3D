/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:11:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 11:16:35 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// Fonction pour remplir une ligne de carte avec les vraies données
int	fill_map_line(char *line, t_data *data, int row)
{
	int	len;
	int	j;

	if (!line || !data || !data->map->grid || row >= data->map->height)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	data->map->grid[row] = ft_my_malloc(data->allocator, data->map->width + 1);
	if (!data->map->grid[row])
		return (0);
	ft_memset(data->map->grid[row], ' ', data->map->width);
	data->map->grid[row][data->map->width] = '\0';
	j = 0;
	while (j < len && j < data->map->width)
	{
		data->map->grid[row][j] = line[j];
		j++;
	}
	return (1);
}

int	parse_map_line(t_data *data, char *line, int *map_row)
{
	if (ft_strlen(line) > 0 && (line [0] == ' '
			|| line[0] == '1' || line[0] == '0'))
	{
		if (!fill_map_line(line, data, *map_row))
			return (0);
		(*map_row)++;
	}
	return (1);
}

int	parse_map(char *filename, t_data **data)
{
	int		fd;
	int		map_row;
	char	*line;

	(*data)->map->grid = ft_my_malloc((*data)->allocator,
			sizeof(char *) * ((*data)->map->height + 1));
	if (!(*data)->map->grid)
		return (0);
	(*data)->map->grid[(*data)->map->height] = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	map_row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_map_line(*data, line, &map_row))
			return (free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
