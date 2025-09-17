/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:23:42 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 14:30:59 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	debug_print_map(t_map *map)
{
	int		i;

	if (!map || !map->grid)
	{
		ft_printf("Map is NULL or grid is NULL\n");
		return ;
	}
	ft_printf("Map dimensions: %d x %d\n", map->height, map->width);
	ft_printf("Map Grid:\n");
	i = 0;
	while (i < map->height && map->grid[i])
	{
		ft_printf("Line %2d: [%s]\n", i, map->grid[i]);
		i++;
	}
	if (i == 0)
		ft_printf("No map lines found!\n");
}

void	debug_print_textures(t_textures *textures)
{
	if (!textures)
		return ;
	ft_printf("North Texture: %s\n", textures->north_texture);
	ft_printf("South Texture: %s\n", textures->south_texture);
	ft_printf("West Texture: %s\n", textures->west_texture);
	ft_printf("East Texture: %s\n", textures->east_texture);
	if (textures->floor_color)
		ft_printf("Floor Color   : %d %d %d\n", textures->floor_color->r,
			textures->floor_color->g, textures->floor_color->b);
	if (textures->ceiling_color)
		ft_printf("Ceiling Color : %d %d %d\n", textures->ceiling_color->r,
			textures->ceiling_color->g, textures->ceiling_color->b);
}

void	debug_print_player(t_player *player)
{
	if (!player)
		return ;
	ft_printf("Player Position: %d %d\n", player->position[0],
		player->position[1]);
	ft_printf("Player Direction: %c\n", player->direction);
}

void	debug_print_data(t_data *data)
{
	if (!data)
		return ;
	debug_print_textures(data->textures);
	debug_print_map(data->map);
	debug_print_player(data->player);
}
