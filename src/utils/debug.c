/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:23:42 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/03 14:03:19 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	debug_print_map(t_map *map)
{
	int		i;

	if (!map || !map->grid)
	{
		printf("Map is NULL or grid is NULL\n");
		return ;
	}
	printf("Map dimensions: %d x %d\n", map->height, map->width);
	printf("Map Grid:\n");
	i = 0;
	while (i < map->height && map->grid[i])
	{
		printf("Line %2d: [%s]\n", i, map->grid[i]);
		i++;
	}
	if (i == 0)
		printf("No map lines found!\n");
}

void	debug_print_textures(t_textures *textures)
{
	if (!textures)
		return ;
	printf("North Texture: %s\n", textures->north_texture);
	printf("South Texture: %s\n", textures->south_texture);
	printf("West Texture: %s\n", textures->west_texture);
	printf("East Texture: %s\n", textures->east_texture);
	if (textures->floor_color)
		printf("Floor Color   : %d %d %d\n", textures->floor_color->r,
			textures->floor_color->g, textures->floor_color->b);
	if (textures->ceiling_color)
		printf("Ceiling Color : %d %d %d\n", textures->ceiling_color->r,
			textures->ceiling_color->g, textures->ceiling_color->b);
}

void	debug_print_player(t_player *player)
{
	if (!player)
		return ;
	printf("Player start_position: %d %d\n", player->start_position[0],
		player->start_position[1]);
	printf("Player Direction: %c\n", player->direction);
}

void	debug_print_data(t_data *data)
{
	if (!data)
		return ;
	debug_print_textures(data->textures);
	debug_print_map(data->map);
	debug_print_player(data->player);
}
