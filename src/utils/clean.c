/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:11:18 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 13:08:49 by mzimeris         ###   ########.fr       */
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
	// if (data->mlx)
	// 	mlx_destroy_window(data->mlx, data->win);
	if (data->player)
		ft_my_free(data->allocator, data->player);
	if (data->map)
		clean_map(data, data->map);
	if (data->textures)
		clean_textures(data, data->textures);
	if (data->ids)
		clean_ids(data, data->ids);
	// if (data->win)
	// 	ft_my_free(data->allocator, data->win);
	// if (data->mlx)
	// 	ft_my_free(data->allocator, data->mlx);
	ft_my_free_all(data->allocator);
}
