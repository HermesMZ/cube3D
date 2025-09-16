/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:11:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:50:16 by mzimeris         ###   ########.fr       */
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

// Fonction pour remplir la carte avec les données du fichier
int	fill_map_from_file(t_data *data)
{
	int	start;
	int	i;
	int	row;
	int	j;
	int	len;

	start = find_map_start(data);
	if (start == -1)
		return (0);
	row = -1;
	i = start - 1;
	while (data->file[++i] && is_map_line(data->file[i])
		&& ++row < data->map->height)
	{
		len = ft_strlen(data->file[i]);
		if (len > 0 && data->file[i][len - 1] == '\n')
			len--;
		j = -1;
		while (++j < len && j < data->map->width)
		{
			data->map->grid[row][j] = data->file[i][j];
		}
	}
	return (1);
}

// Fonction pour parser la carte depuis data->file
int	parse_map_from_file(t_data **data)
{
	if (!count_map_dimensions(*data))
		return (0);
	if (!allocate_map_grid(*data))
		return (0);
	if (!fill_map_from_file(*data))
		return (0);
	return (1);
}
