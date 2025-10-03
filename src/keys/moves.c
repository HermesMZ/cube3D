/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:43:36 by zoum              #+#    #+#             */
/*   Updated: 2025/10/03 15:03:50 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x + data->player->dir_x
		* data->player->movement_speed;
	new_y = data->player->y + data->player->dir_y
		* data->player->movement_speed;
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

	new_x = data->player->x - data->player->dir_x
		* data->player->movement_speed;
	new_y = data->player->y - data->player->dir_y
		* data->player->movement_speed;
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

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	rot_speed = data->player->rotation_speed;
	data->player->dir_x = data->player->dir_x * cos(rot_speed)
		- data->player->dir_y * sin(rot_speed);
	data->player->dir_y = old_dir_x * sin(rot_speed)
		+ data->player->dir_y * cos(rot_speed);
	data->player->plane_x = data->player->plane_x * cos(rot_speed)
		- data->player->plane_y * sin(rot_speed);
	data->player->plane_y = old_plane_x * sin(rot_speed)
		+ data->player->plane_y * cos(rot_speed);
}

void	turn_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	rot_speed = data->player->rotation_speed;
	data->player->dir_x = data->player->dir_x * cos(-rot_speed)
		- data->player->dir_y * sin(-rot_speed);
	data->player->dir_y = old_dir_x * sin(-rot_speed)
		+ data->player->dir_y * cos(-rot_speed);
	data->player->plane_x = data->player->plane_x * cos(-rot_speed)
		- data->player->plane_y * sin(-rot_speed);
	data->player->plane_y = old_plane_x * sin(-rot_speed)
		+ data->player->plane_y * cos(-rot_speed);
}
