/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:21:21 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/28 13:33:42 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	set_player_position_h(t_data *data)
{
	if (data->player->direction == 'E')
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = 0.66;
	}
	else if (data->player->direction == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = -0.66;
	}
}

void	set_player_position(t_data *data)
{
	if (data->player->direction == 'N')
	{
		data->player->dir_x = 0;
		data->player->dir_y = -1;
		data->player->plane_x = 0.66;
		data->player->plane_y = 0;
	}
	else if (data->player->direction == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
		data->player->plane_x = -0.66;
		data->player->plane_y = 0;
	}
	else
		set_player_position_h(data);
}

static void	set_player_attribute(t_data *data, int i, int j)
{
	data->player->direction = data->map->grid[i][j];
	data->player->start_position[0] = i;
	data->player->start_position[1] = j;
	data->player->movement_speed = 0.05;
	data->player->rotation_speed = 0.05;
	data->player->base_speed = 0.05;
	data->player->y = i + 0.5;
	data->player->x = j + 0.5;
	data->player->mouse_sensitivity = 0.001;
	data->player->last_mouse_x = W / 2;
	data->player->last_mouse_y = H / 2;
	data->player->first_mouse = true;
}

int	init_player(t_data *data, int i, int j)
{
	int	player_count;

	if (!data || !data->map || !data->map->grid)
		return (0);
	data->player = ft_my_malloc(data->allocator, sizeof(t_player));
	if (!data->player)
		return (0);
	*data->player = (t_player){0};
	player_count = 0;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			if (data->map->grid[i][j] == 'N' || data->map->grid[i][j] == 'S'
				|| data->map->grid[i][j] == 'E' || data->map->grid[i][j] == 'W')
			{
				set_player_attribute(data, i, j);
				set_player_position(data);
				player_count++;
			}
		}
	}
	return (player_count);
}
