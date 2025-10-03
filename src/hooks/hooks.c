/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:11:07 by zoum              #+#    #+#             */
/*   Updated: 2025/10/02 19:29:44 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keysym, t_data *data)
{
	printf("Key pressed: %d\n", keysym);
	if (keysym == XK_Escape)
		end_display(data);
	if (keysym == 32)
		handle_fire_key(data);
	if (keysym == 101)
		handle_open_key(data);
	if (keysym == 65289)
		data->keys.minimap = true;
	if (keysym == 119)
		data->keys.forward = true;
	if (keysym == 115)
		data->keys.backward = true;
	if (keysym == 97)
		data->keys.left = true;
	if (keysym == 100)
		data->keys.right = true;
	if (keysym == 101)
		data->keys.strafe_right = true;
	if (keysym == 113)
		data->keys.strafe_left = true;
	if (keysym == 65505)
		data->keys.run = true;
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	if (keysym == 65289)
		data->keys.minimap = false;
	if (keysym == 119)
		data->keys.forward = false;
	if (keysym == 115)
		data->keys.backward = false;
	if (keysym == 97)
		data->keys.left = false;
	if (keysym == 100)
		data->keys.right = false;
	if (keysym == 101)
		data->keys.strafe_right = false;
	if (keysym == 113)
		data->keys.strafe_left = false;
	if (keysym == 65505)
		data->keys.run = false;
	return (0);
}

int	update(t_data *data)
{
	static int frame_count = 0;
	
    handle_move_keys(data);
	if (data->keys.backward || data->keys.forward
		|| data->keys.left || data->keys.right
		|| data->keys.strafe_left || data->keys.strafe_right || frame_count == 0)
		{
			frame_count = 1;
			render_3d_scene(data);
		}
    mlx_put_image_to_window(data->mlx->mlx_ptr,
							data->mlx->win_ptr,
							data->mlx->img->img, 0, 0);
    return (0);
}
