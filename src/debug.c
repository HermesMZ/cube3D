/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:23:42 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/15 16:25:14 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	debug_print_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		ft_printf("%s\n", map->grid[i]);
		i++;
	}
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
		ft_printf("Floor Color: %s\n", textures->floor_color);
	if (textures->ceiling_color)
		ft_printf("Ceiling Color: %s\n", textures->ceiling_color);
}

void	debug_print_player(t_player *player)
{
	if (!player)
		return ;
	ft_printf("Player Position: %c\n", player->position);
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
