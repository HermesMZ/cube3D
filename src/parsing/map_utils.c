/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 19:00:10 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Fonction pour déterminer si une ligne fait partie de la carte
int	is_map_line(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len == 0)
		return (0);
	return (line[0] == '1' || line[0] == '0' || line[0] == ' ');
}

int	count_map_dimensions(t_data *data, char *line, int fd)
{
	int	len;

	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len > data->map->width)
			data->map->width = len;
		data->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (data->map->height > 0 && data->map->width > 0);
}
