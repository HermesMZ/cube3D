/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:43:36 by zoum              #+#    #+#             */
/*   Updated: 2025/10/04 13:34:19 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;
	int		xoffset;

	data = (t_data *)param;
	if (data->player->first_mouse)
	{
		data->player->last_mouse_x = x;
		data->player->last_mouse_y = y;
		data->player->first_mouse = false;
		return (0);
	}
	xoffset = x - data->player->last_mouse_x;
	data->player->last_mouse_x = x;
	data->player->last_mouse_y = y;
	if (xoffset > data->player->mouse_sensitivity)
		turn_right(data);
	else if (xoffset < -data->player->mouse_sensitivity)
		turn_left(data);
	if (x <= 10 || x >= W - 10)
	{
		mlx_mouse_move(data->mlx->mlx_ptr, data->mlx->win_ptr, W / 2, H / 2);
		data->player->last_mouse_x = W / 2;
		data->player->last_mouse_y = H / 2;
	}
	return (0);
}

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
