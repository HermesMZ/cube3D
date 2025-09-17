/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:11:07 by zoum              #+#    #+#             */
/*   Updated: 2025/09/17 23:19:08 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		end_display(data);
	if (keysym == XK_space)
		handle_fire_key(data);
	if (keysym == XK_E)
		handle_open_key(data);
	if (keysym == XK_Tab)
		data->keys.minimap = 1;
	if (keysym == XK_W)
		data->keys.forward = 1;
	if (keysym == XK_S)
		data->keys.backward = 1;
	if (keysym == XK_A)
		data->keys.left = 1;
	if (keysym == XK_D)
		data->keys.right = 1;
	if (keysym == XK_Shift_L)
		data->keys.strafe = 1;
	if (keysym == XK_Control_L)
		data->keys.run = 1;
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	if (keysym == XK_Tab)
		data->keys.minimap = 0;
	if (keysym == XK_W)
		data->keys.forward = 0;
	if (keysym == XK_S)
		data->keys.backward = 0;
	if (keysym == XK_A)
		data->keys.left = 0;
	if (keysym == XK_D)
		data->keys.right = 0;
	if (keysym == XK_Shift_L)
		data->keys.strafe = 0;
	if (keysym == XK_Control_L)
		data->keys.run = 0;
	return (0);
}
