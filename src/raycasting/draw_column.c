/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:34:25 by edobele           #+#    #+#             */
/*   Updated: 2025/10/03 14:53:59 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_my_img	*select_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&data->textures->east_img);
		else
			return (&data->textures->west_img);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&data->textures->south_img);
		else
			return (&data->textures->north_img);
	}
}

int	calculate_tex_x(t_ray *ray, t_data *data, t_my_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = data->player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(tex->width));
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_ceiling(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	ceiling_rgb;

	ceiling_rgb = create_rgb(data->textures->ceiling_color->r,
			data->textures->ceiling_color->g,
			data->textures->ceiling_color->b);
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(data->mlx->img, x, y, ceiling_rgb);
		y++;
	}
}

void	draw_wall(t_data *data, t_ray *ray, int x, t_my_img *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;

	tex_x = calculate_tex_x(ray, data, tex);
	step = (double)tex->height / (double)ray->line_height;
	tex_pos = (ray->draw_start - data->mlx->height / 2.0
			+ (double)ray->line_height / 2.0) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel(data->mlx->img, x, y, *(int *)(tex->addr + (tex_y
					* tex->line_len + tex_x * (tex->bits_per_pixel / 8))));
		tex_pos += step;
		y++;
	}
}

void	draw_floor(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	floor_rgb;

	floor_rgb = create_rgb(data->textures->floor_color->r,
			data->textures->floor_color->g,
			data->textures->floor_color->b);
	y = ray->draw_end + 1;
	while (y < data->mlx->height && y >= 0)
	{
		put_pixel(data->mlx->img, x, y, floor_rgb);
		y++;
	}
}
