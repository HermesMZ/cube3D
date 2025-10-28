/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:55:24 by edobele           #+#    #+#             */
/*   Updated: 2025/10/28 18:27:10 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	update(t_data *data)
{
	handle_move_keys(data);
	render_3d_scene(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->mlx->img->img, 0, 0);
	return (0);
}

void	render_3d_scene(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < data->mlx->width)
	{
		init_ray(&ray, data, x);
		perform_dda(&ray, data);
		compute_wall(&ray, data);
		draw_column(&ray, data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
		data->mlx->img->img, 0, 0);
	render_map2d(data, W / 100);
}

void	perform_dda(t_ray *ray, t_data *data)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map->width
			|| ray->map_y < 0 || ray->map_y >= data->map->height)
			ray->hit = 1;
		else if (data->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	compute_wall(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->wall_rgb = 0xFF0000;
		else
			ray->wall_rgb = 0x00FF00;
		ray->perp_wall_dist = (ray->map_x - data->player->x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->wall_rgb = 0x0000FF;
		else
			ray->wall_rgb = 0xFFFF00;
		ray->perp_wall_dist = (ray->map_y - data->player->y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
	ray->line_height = (int)(data->mlx->height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + data->mlx->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->mlx->height / 2;
	if (ray->draw_end >= data->mlx->height)
		ray->draw_end = data->mlx->height - 1;
}

void	draw_column(t_ray *ray, t_data *data, int x)
{
	t_my_img	*tex;

	draw_ceiling(data, ray, x);
	tex = select_texture(ray, data);
	draw_wall(data, ray, x, tex);
	draw_floor(data, ray, x);
}
