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
	if (keysym == 32)
		handle_fire_key(data);
	if (keysym == 101)
		handle_open_key(data);
	if (keysym == 65289)
		data->keys.minimap = true;
	if (keysym == 122)
		data->keys.forward = true;
	if (keysym == 115)
		data->keys.backward = true;
	if (keysym == 113)
		data->keys.left = true;
	if (keysym == 100)
		data->keys.right = true;
	if (keysym == 65505)
		data->keys.strafe = true;
	if (keysym == 65507)
		data->keys.run = true;
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	if (keysym == 65289)
		data->keys.minimap = 0;
	if (keysym == 122)
		data->keys.forward = 0;
	if (keysym == 115)
		data->keys.backward = 0;
	if (keysym == 113)
		data->keys.left = 0;
	if (keysym == 100)
		data->keys.right = 0;
	if (keysym == 65505)
		data->keys.strafe = 0;
	if (keysym == 65507)
		data->keys.run = 0;
	return (0);
}

int	update(void *param)
{
	t_data *data = (t_data *)param;

	handle_move_keys(data);
	render_map2d(data, 23);
	return (0);
}
