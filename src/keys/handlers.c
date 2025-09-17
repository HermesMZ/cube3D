/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:53:07 by zoum              #+#    #+#             */
/*   Updated: 2025/10/04 13:33:27 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_move_keys(t_data *data)
{
	handle_run_key(data);
	if (data->keys.forward)
		move_forward(data);
	if (data->keys.backward)
		move_backward(data);
	if (data->keys.left)
		turn_left(data);
	if (data->keys.right)
		turn_right(data);
	if (data->keys.strafe_right)
		translate_right(data);
	if (data->keys.strafe_left)
		translate_left(data);
}

void	handle_run_key(t_data *data)
{
	if (data->keys.run)
		data->player->movement_speed = data->player->base_speed * 3;
	else
		data->player->movement_speed = data->player->base_speed;
}
