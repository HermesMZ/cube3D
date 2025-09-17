/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:53:07 by zoum              #+#    #+#             */
/*   Updated: 2025/09/17 22:53:14 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	handle_move_keys(t_data *data)
{
	if (data->keys.forward)
		move_forward(data);
	if (data->keys.backward)
		move_backward(data);
	if (data->keys.left && !data->keys.strafe)
		turn_left(data);
	if (data->keys.right && !data->keys.strafe)
		turn_right(data);
}

void	handle_strafe_keys(t_data *data)
{
	if (data->keys.strafe && data->keys.left)
		translate_left(data);
	if (data->keys.strafe && data->keys.right)
		translate_right(data);
}

// gère la vitesse de déplacement et de rotation
void	handle_run_key(t_data *data)
{
	if (data->keys.run)
	{

	}
	else
	{

	}
}
