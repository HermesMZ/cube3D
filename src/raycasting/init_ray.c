#include "cub3D.h"

static void	init_ray_direction(t_ray *ray, t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)data->mlx->width - 1;
	ray->ray_dir_x = data->player->dir_x + data->player->plane_x
		* ray->camera_x;
	ray->ray_dir_y = data->player->dir_y + data->player->plane_y
		* ray->camera_x;
	ray->map_x = (int)data->player->x;
	ray->map_y = (int)data->player->y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = DBL_MAX;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = DBL_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_ray_steps(t_ray *ray, t_data *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player->x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player->y)
			* ray->delta_dist_y;
	}
}

void	init_ray(t_ray *ray, t_data *data, int x)
{
	init_ray_direction(ray, data, x);
	init_ray_steps(ray, data);
	ray->hit = 0;
	ray->wall_rgb = 0x000000;
}
