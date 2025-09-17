/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:50 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 23:53:13 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// gerer la resolution de la fenetre
int	init_mlx(t_data *data)
{
	data->mlx = ft_my_malloc(data->allocator, sizeof(t_mlx_data));
	if (!data->mlx)
		return (0);
	*data->mlx = (t_mlx_data){0};
	data->mlx->mlx_ptr = mlx_init();
	if (!data->mlx->mlx_ptr)
		return (0);
	data->mlx->win_ptr = mlx_new_window(data->mlx->mlx_ptr, 800, 600, "Cube3D");
	if (!data->mlx->win_ptr)
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
	if (!init_mlx(*data))
		return (clean_data(*data), 0);
	return (1);
}
