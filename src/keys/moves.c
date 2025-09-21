/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:43:36 by zoum              #+#    #+#             */
/*   Updated: 2025/09/17 23:40:58 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	move_forward(t_data *data)
{
	double newX;
	double newY;

	newX = data->player->x + data->player->dirX * data->player->movement_speed;
	newY = data->player->y + data->player->dirY * data->player->movement_speed;
	if (data->map->grid[(int)newY][(int)newX] != '1')
	{
		data->player->x = newX;
		data->player->y = newY;
	}
}

void	move_backward(t_data *data)
{
	double newX;
	double newY;

	newX = data->player->x - data->player->dirX * data->player->movement_speed;
	newY = data->player->y - data->player->dirY * data->player->movement_speed;
	if (data->map->grid[(int)newY][(int)newX] != '1')
	{
		data->player->x = newX;
		data->player->y = newY;
	}
}

void	turn_right(t_data *data)
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

void	turn_left(t_data *data)
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
