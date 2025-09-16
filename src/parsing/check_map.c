/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:32:20 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:40:01 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_map_closed(t_map *map)
{
	(void)map; // Pour éviter l'erreur de paramètre non utilisé
	// TODO: Implémenter la vérification que la carte est fermée
	return (1);
}

int	map_check(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] != '1' && map->grid[i][j] != '0'
				&& map->grid[i][j] != ' ' && map->grid[i][j] != 'N'
				&& map->grid[i][j] != 'S' && map->grid[i][j] != 'E'
				&& map->grid[i][j] != 'W')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
