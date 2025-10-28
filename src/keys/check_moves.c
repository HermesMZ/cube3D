/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:22:29 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/28 18:24:13 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WALL_MARGIN 0.2

int	is_wall_at(t_data *data, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_x >= data->map->width
		|| grid_y < 0 || grid_y >= data->map->height)
		return (1);
	return (data->map->grid[grid_y][grid_x] == '1');
}

int	check_collision(t_data *data, double new_x, double new_y)
{
	if (is_wall_at(data, new_x + WALL_MARGIN, new_y + WALL_MARGIN)
		|| is_wall_at(data, new_x + WALL_MARGIN, new_y - WALL_MARGIN)
		|| is_wall_at(data, new_x - WALL_MARGIN, new_y - WALL_MARGIN)
		|| is_wall_at(data, new_x - WALL_MARGIN, new_y + WALL_MARGIN))
		return (1);
	return (0);
}
