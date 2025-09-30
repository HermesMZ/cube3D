/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:42:53 by zoum              #+#    #+#             */
/*   Updated: 2025/09/30 17:14:57 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	translate_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x - data->player->dirY * data->player->movement_speed;
	new_y = data->player->y + data->player->dirX * data->player->movement_speed;
	if (data->map->grid[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}

void	translate_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x + data->player->dirY * data->player->movement_speed;
	new_y = data->player->y - data->player->dirX * data->player->movement_speed;
	if (data->map->grid[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}
