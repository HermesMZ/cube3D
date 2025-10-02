/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:34:25 by edobele           #+#    #+#             */
/*   Updated: 2025/10/02 12:36:14 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_my_img	*select_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			return (&data->textures->east_img);
		else
			return (&data->textures->west_img);
	}
	else
	{
		if (ray->rayDirY > 0)
			return (&data->textures->south_img);
		else
			return (&data->textures->north_img);
	}
}

static int	calculate_tex_x(t_ray *ray, t_data *data, t_my_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = data->player->y + ray->perpWallDist * ray->rayDirY;
	else
		wall_x = data->player->x + ray->perpWallDist * ray->rayDirX;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(tex->width));
	if ((ray->side == 0 && ray->rayDirX > 0)
		|| (ray->side == 1 && ray->rayDirY < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_ceiling(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	ceiling_rgb;

	ceiling_rgb = create_rgb(data->textures->ceiling_color->r,
			data->textures->ceiling_color->g,
			data->textures->ceiling_color->b);
	y = 0;
	while (y < ray->drawStart)
	{
		put_pixel(data->mlx->img, x, y, ceiling_rgb);
		y++;
	}
}

static void	draw_wall(t_data *data, t_ray *ray, int x, t_my_img *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	int		color;

	tex_x = calculate_tex_x(ray, data, tex);
	step = (double)tex->height / (double)ray->lineHeight;
	tex_pos = (ray->drawStart - data->mlx->height / 2.0 + (double)ray->lineHeight / 2.0) * step;
	y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = *(int *)(tex->addr + (tex_y * tex->line_len
					+ tex_x * (tex->bits_per_pixel / 8)));
		put_pixel(data->mlx->img, x, y, color);
		tex_pos += step;
		y++;
	}
}

static void	draw_floor(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	floor_rgb;

	floor_rgb = create_rgb(data->textures->floor_color->r,
			data->textures->floor_color->g,
			data->textures->floor_color->b);
	y = ray->drawEnd + 1;
	while (y < data->mlx->height)
	{
		put_pixel(data->mlx->img, x, y, floor_rgb);
		y++;
	}
}

void	draw_column(t_ray *ray, t_data *data, int x)
{
	t_my_img	*tex;

	draw_ceiling(data, ray, x);
	tex = select_texture(ray, data);
	draw_wall(data, ray, x, tex);
	draw_floor(data, ray, x);
}
