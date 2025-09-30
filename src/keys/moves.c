/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:43:36 by zoum              #+#    #+#             */
/*   Updated: 2025/09/30 17:02:11 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x + data->player->dirX * data->player->movement_speed;
	new_y = data->player->y + data->player->dirY * data->player->movement_speed;
	if (data->map->grid[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x - data->player->dirX * data->player->movement_speed;
	new_y = data->player->y - data->player->dirY * data->player->movement_speed;
	if (data->map->grid[(int)new_y][(int)new_x] != '1')
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
}

void	turn_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = data->player->dirX;
	old_plane_x = data->player->planeX;
	rot_speed = data->player->rotation_speed;
	data->player->dirX = data->player->dirX * cos(rot_speed)
		- data->player->dirY * sin(rot_speed);
	data->player->dirY = old_dir_x * sin(rot_speed)
		+ data->player->dirY * cos(rot_speed);
	data->player->planeX = data->player->planeX * cos(rot_speed)
		- data->player->planeY * sin(rot_speed);
	data->player->planeY = old_plane_x * sin(rot_speed)
		+ data->player->planeY * cos(rot_speed);
}

void	turn_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = data->player->dirX;
	old_plane_x = data->player->planeX;
	rot_speed = data->player->rotation_speed;
	data->player->dirX = data->player->dirX * cos(-rot_speed)
		- data->player->dirY * sin(-rot_speed);
	data->player->dirY = old_dir_x * sin(-rot_speed)
		+ data->player->dirY * cos(-rot_speed);
	data->player->planeX = data->player->planeX * cos(-rot_speed)
		- data->player->planeY * sin(-rot_speed);
	data->player->planeY = old_plane_x * sin(-rot_speed)
		+ data->player->planeY * cos(-rot_speed);
}
