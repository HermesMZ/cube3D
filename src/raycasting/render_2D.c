/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:36:01 by edobele           #+#    #+#             */
/*   Updated: 2025/10/02 12:36:07 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	render_tile(t_data *data, int i, int j, int tile_size)
{
	int	color;
	int	x;
	int	y;

	if (data->map->grid[i][j] == '1')
		color = create_rgb(0, 0, 0);
	else
		color = create_rgb(255, 255, 255);
	y = 0;
	while (y < tile_size)
	{
		x = 0;
		while (x < tile_size)
		{
			put_pixel(data->mlx->img, j * tile_size + x,
				i * tile_size + y, color);
			x++;
		}
		y++;
	}
}

static void	render_player(t_data *data, int tile_size)
{
	int	px;
	int	py;
	int	dx;
	int	dy;

	px = (int)(data->player->x * tile_size);
	py = (int)(data->player->y * tile_size);
	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			put_pixel(data->mlx->img, px + dx, py + dy,
				create_rgb(255, 0, 0));
			dx++;
		}
		dy++;
	}
}

void	render_map2d(t_data *data, int tile_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			render_tile(data, i, j, tile_size);
			j++;
		}
		i++;
	}
	render_player(data, tile_size);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr,
		data->mlx->img->img, 0, 0);
}
