/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:40:17 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/28 13:22:04 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
