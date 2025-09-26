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
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	oldDirX = data->player->dirX;
	oldPlaneX = data->player->planeX;
	rotSpeed = data->player->rotation_speed;
	data->player->dirX = data->player->dirX * cos(rotSpeed) - data->player->dirY * sin(rotSpeed);
	data->player->dirY = oldDirX * sin(rotSpeed) + data->player->dirY * cos(rotSpeed);
	data->player->planeX = data->player->planeX * cos(rotSpeed) - data->player->planeY * sin(rotSpeed);
	data->player->planeY = oldPlaneX * sin(rotSpeed) + data->player->planeY * cos(rotSpeed);
}

void	turn_left(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	oldDirX = data->player->dirX;
	oldPlaneX = data->player->planeX;
	rotSpeed = data->player->rotation_speed;
	data->player->dirX = data->player->dirX * cos(-rotSpeed) - data->player->dirY * sin(-rotSpeed);
	data->player->dirY = oldDirX * sin(-rotSpeed) + data->player->dirY * cos(-rotSpeed);
	data->player->planeX = data->player->planeX * cos(-rotSpeed) - data->player->planeY * sin(-rotSpeed);
	data->player->planeY = oldPlaneX * sin(-rotSpeed) + data->player->planeY * cos(-rotSpeed);
}
