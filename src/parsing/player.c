/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:21:21 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/30 17:13:06 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// si le joueur regarde au nord l'axe horizontale (x) ne change pas 
// par contre l'axe vertical change, on travail dans une plage de [-1, 1]
// plane correspond a l'angle de vue (FOV), 0.66 permet au mur d'étre carré
// on applique toute ces valeurs en fonction de la ou on regarde

static void	set_player_direction_ew(t_data *data)
{
	if (data->player->direction == 'E')
	{
		data->player->dirX = 1;
		data->player->dirY = 0;
		data->player->planeX = 0;
		data->player->planeY = 0.66;
	}
	else if (data->player->direction == 'W')
	{
		data->player->dirX = -1;
		data->player->dirY = 0;
		data->player->planeX = 0;
		data->player->planeY = -0.66;
	}
}

static void	set_player_direction(t_data *data)
{
	if (data->player->direction == 'N')
	{
		data->player->dirX = 0;
		data->player->dirY = -1;
		data->player->planeX = 0.66;
		data->player->planeY = 0;
	}
	else if (data->player->direction == 'S')
	{
		data->player->dirX = 0;
		data->player->dirY = 1;
		data->player->planeX = -0.66;
		data->player->planeY = 0;
	}
	else
		set_player_direction_ew(data);
}

void	set_player_attributes(t_data *data, int i, int j)
{
	if (!data || !data->player)
		return ;
	data->player->direction = data->map->grid[i][j];
	data->player->start_position[0] = i;
	data->player->start_position[1] = j;
	data->player->movement_speed = 0.05;
	data->player->rotation_speed = 0.05;
	data->player->base_speed = 0.05;
	data->player->y = i + 0.5;
	data->player->x = j + 0.5;
	set_player_direction(data);
}

int	init_player(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	if (!data || !data->map || !data->map->grid || !data->player)
		return (0);
	player_count = 0;
	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			if (data->map->grid[i][j] == 'N' || data->map->grid[i][j] == 'S'
				|| data->map->grid[i][j] == 'E' || data->map->grid[i][j] == 'W')
			{
				set_player_attributes(data, i, j);
				player_count++;
			}
		}
	}
	return (player_count);
}
