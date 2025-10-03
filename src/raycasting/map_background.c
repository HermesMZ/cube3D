/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:54:50 by edobele           #+#    #+#             */
/*   Updated: 2025/10/03 14:54:57 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_my_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int r, int g, int b)
{
	return ((r * 65536) + (g * 256) + b);
}

void	render_background(t_data *data, int x, int y)
{
	int	ceiling_rgb;
	int	floor_rgb;

	ceiling_rgb = create_rgb(data->textures->ceiling_color->r,
			data->textures->ceiling_color->g, data->textures->ceiling_color->b);
	floor_rgb = create_rgb(data->textures->floor_color->r,
			data->textures->floor_color->g, data->textures->floor_color->b);
	while (y < data->mlx->height)
	{
		x = 0;
		while (x < data->mlx->width)
		{
			if (y < data->mlx->height / 2)
				put_pixel(data->mlx->img, x, y, ceiling_rgb);
			else
				put_pixel(data->mlx->img, x, y, floor_rgb);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->mlx->img->img, 0, 0);
}
