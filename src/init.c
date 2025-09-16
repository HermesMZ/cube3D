/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:50 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:40:01 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	if (!data->win)
		return (free(data->mlx), 0);
	return (1);
}

int	init_textures(t_data *data)
{
	if (!data || !data->textures)
		return (0);
	data->textures->north_texture = NULL;
	data->textures->south_texture = NULL;
	data->textures->west_texture = NULL;
	data->textures->east_texture = NULL;
	data->textures->floor_color = ft_my_malloc(data->allocator,
			sizeof(t_color));
	if (!data->textures->floor_color)
		return (0);
	data->textures->ceiling_color = ft_my_malloc(data->allocator,
			sizeof(t_color));
	if (!data->textures->ceiling_color)
		return (0);
	return (1);
}

int	init_data(t_data **data, t_lalloc *allocator)
{
	*data = ft_my_malloc(allocator, sizeof(t_data));
	if (!*data)
		return (0);
	**data = (t_data){0};
	(*data)->allocator = allocator;
	(*data)->textures = ft_my_malloc(allocator, sizeof(t_textures));
	if (!(*data)->textures)
		return (clean_data(*data), 0);
	if (!init_textures(*data))
		return (clean_data(*data), 0);
	(*data)->map = ft_my_malloc(allocator, sizeof(t_map));
	if (!(*data)->map)
		return (clean_data(*data), 0);
	*(*data)->map = (t_map){0};
	(*data)->player = ft_my_malloc(allocator, sizeof(t_player));
	if (!(*data)->player)
		return (clean_data(*data), 0);
	*(*data)->player = (t_player){0};
	// if (!init_mlx(*data))
	// 	return (clean_data(*data), 0);
	return (1);
}
