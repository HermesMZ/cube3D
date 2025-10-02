/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:42:53 by zoum              #+#    #+#             */
/*   Updated: 2025/10/02 14:10:23 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	translate_left(t_data *data)
{
	double newX;
	double newY;

	newX = data->player->x + data->player->dirY * data->player->movement_speed;
	newY = data->player->y - data->player->dirX * data->player->movement_speed;
	if (data->map->grid[(int)newY][(int)newX] != '1')
	{
		data->player->x = newX;
		data->player->y = newY;
	}
}

void	translate_right(t_data *data)
{
	double newX;
	double newY;

	newX = data->player->x - data->player->dirY * data->player->movement_speed;
	newY = data->player->y + data->player->dirX * data->player->movement_speed;
	if (data->map->grid[(int)newY][(int)newX] != '1')
	{
		data->player->x = newX;
		data->player->y = newY;
	}
}
