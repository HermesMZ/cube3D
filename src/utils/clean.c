/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:11:18 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/03 13:18:19 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	clean_ids(t_data *data, t_id *ids)
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

static void	clean_map(t_data *data, t_map *map)
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

static void	clean_textures(t_data *data, t_textures *textures)
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

static void	destroy_texture_images(t_data *data)
{
	if (!data || !data->textures)
		return ;
	if (data->textures->north_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->north_img.img);
	if (data->textures->south_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->south_img.img);
	if (data->textures->west_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->west_img.img);
	if (data->textures->east_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->east_img.img);
}

int	end_display(t_data *data)
{
	if (!data)
		exit(0);
	if (data->mlx)
	{
		destroy_texture_images(data);
		if (data->mlx->img && data->mlx->img->img)
			mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img->img);
		if (data->mlx->win_ptr)
			mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
		if (data->mlx->mlx_ptr)
		{
			mlx_destroy_display(data->mlx->mlx_ptr);
			free(data->mlx->mlx_ptr);
		}
		if (data->mlx->img)
			ft_my_free(data->allocator, data->mlx->img);
		ft_my_free(data->allocator, data->mlx);
	}
	clean_data(data);
	exit(0);
	return (0);
}
