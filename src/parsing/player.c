/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:21:21 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/02 13:47:51 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
				data->player->direction = data->map->grid[i][j];
				data->player->start_position[0] = i;
				data->player->start_position[1] = j;
				data->player->movement_speed = 0.01;
				data->player->rotation_speed = 0.01;
				data->player->base_speed = 0.05;
				data->player->y = i + 0.5;
				data->player->x = j + 0.5;
				set_player_attribute(data);
				player_count++;
			}
		}
	}
	return (player_count);
}

void	set_player_attribute(t_data *data)
{
	if (data->player->direction == 'N') {
		data->player->dirX = 0;  // si le joueur regarde au nord l'axe horizontale (x) ne change pas 
		data->player->dirY = -1; // par contre l'axe vertical change, on travail dans une plage de [-1, 1]
		data->player->planeX = 0.66; // plane correspond a l'angle de vue (FOV), 0.66 permet au mur d'étre carré
		data->player->planeY = 0; // on applique toute ces valeurs en fonction de la ou on regarde
	}
	else if (data->player->direction == 'S') {
		data->player->dirX = 0;
		data->player->dirY = 1;
		data->player->planeX = -0.66;
		data->player->planeY = 0;
	}
	else if (data->player->direction == 'E') {
		data->player->dirX = 1;
		data->player->dirY = 0;
		data->player->planeX = 0;
		data->player->planeY = 0.66;
	}
	else if (data->player->direction == 'W') {
		data->player->dirX = -1;
		data->player->dirY = 0;
		data->player->planeX = 0;
		data->player->planeY = -0.66;
	}
}
