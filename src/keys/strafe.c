/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:42:53 by zoum              #+#    #+#             */
/*   Updated: 2025/10/03 15:04:04 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	translate_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x + data->player->dir_y
		* data->player->movement_speed;
	new_y = data->player->y - data->player->dir_x
		* data->player->movement_speed;
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

	new_x = data->player->x - data->player->dir_y
		* data->player->movement_speed;
	new_y = data->player->y + data->player->dir_x
		* data->player->movement_speed;
	if (data->map->grid[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}
