/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:21:21 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 22:31:01 by zoum             ###   ########.fr       */
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
				player_count++;
			}
		}
	}
	return (player_count);
}
