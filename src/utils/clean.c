/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:11:18 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 23:58:44 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_ids(t_data *data, t_id *ids)
{
	t_id	*current;
	t_id	*next;

	if (!ids)
		return ;
	current = ids;
	while (current)
	{
		next = current->next;
		if (current->key)
			ft_my_free(data->allocator, current->key);
		if (current->value)
			ft_my_free(data->allocator, current->value);
		ft_my_free(data->allocator, current);
		current = next;
	}
}

void	clean_map(t_data *data, t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->height)
	{
		ft_my_free(data->allocator, map->grid[i]);
		i++;
	}
	ft_my_free(data->allocator, map->grid);
	ft_my_free(data->allocator, map);
}

void	clean_textures(t_data *data, t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->north_texture)
		ft_my_free(data->allocator, textures->north_texture);
	if (textures->south_texture)
		ft_my_free(data->allocator, textures->south_texture);
	if (textures->west_texture)
		ft_my_free(data->allocator, textures->west_texture);
	if (textures->east_texture)
		ft_my_free(data->allocator, textures->east_texture);
	if (textures->floor_color)
		ft_my_free(data->allocator, textures->floor_color);
	if (textures->ceiling_color)
		ft_my_free(data->allocator, textures->ceiling_color);
	ft_my_free(data->allocator, textures);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->player)
		ft_my_free(data->allocator, data->player);
	if (data->map)
		clean_map(data, data->map);
	if (data->textures)
		clean_textures(data, data->textures);
	if (data->ids)
		clean_ids(data, data->ids);
	ft_my_free_all(data->allocator);
}

int	end_display(t_data *data)
{
	if (data && data->mlx && data->mlx->img && data->mlx->img->img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img->img);
	if (data && data->mlx && data->mlx->img)
		free(data->mlx->img);
	if (data && data->mlx && data->mlx->win_ptr)
		mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
	if (data && data->mlx && data->mlx->mlx_ptr)
	{
		mlx_destroy_display(data->mlx->mlx_ptr);
		free(data->mlx->mlx_ptr);
	}
	if (data && data->mlx)
		ft_my_free(data->allocator, data->mlx);
	if (data)
		clean_data(data);
	exit(0);
	return (0);
}
