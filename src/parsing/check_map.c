/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:32:20 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 15:11:14 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_cell(char c)
{
	return (c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	check_cell(t_map *map, int i, int j)
{
	if (i < 0 || i >= map->height || j < 0 || j >= map->width)
		return (1);
	if ((i > 0 && map->grid[i - 1][j] == ' ')
		|| (i < map->height - 1 && (map->grid[i + 1][j] == ' ')))
		return (1);
	if ((j > 0 && map->grid[i][j - 1] == ' ')
		|| (j < map->width - 1 && map->grid[i][j + 1] == ' '))
		return (1);
	return (0);
}

int	is_map_closed(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid)
		return (1);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (is_valid_cell(map->grid[i][j])
				&& (i == 0 || i == map->height - 1
				|| j == 0 || j == map->width - 1))
				return (1);
			else if (is_valid_cell(map->grid[i][j]) && check_cell(map, i, j))
				return (1);
		}
	}
	return (0);
}

int	map_check(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] != '1' && map->grid[i][j] != '0'
				&& map->grid[i][j] != ' ' && map->grid[i][j] != 'N'
				&& map->grid[i][j] != 'S' && map->grid[i][j] != 'E'
				&& map->grid[i][j] != 'W')
				return (0);
			j++;
		}
		i++;
	}
	if (is_map_closed(map))
		return (0);
	return (1);
}
	