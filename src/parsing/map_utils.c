/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:46:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:46:46 by mzimeris         ###   ########.fr       */
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

// Fonction pour trouver le début de la carte dans data->file
int	find_map_start(t_data *data)
{
	int	i;

	if (!data->file)
		return (-1);
	i = 0;
	while (data->file[i])
	{
		if (is_map_line(data->file[i]))
			return (i);
		i++;
	}
	return (-1);
}

// Fonction pour compter les dimensions de la carte
int	count_map_dimensions(t_data *data)
{
	int	start;
	int	i;
	int	len;

	start = find_map_start(data);
	if (start == -1)
		return (0);
	data->map->height = 0;
	data->map->width = 0;
	i = start;
	while (data->file[i] && is_map_line(data->file[i]))
	{
		len = ft_strlen(data->file[i]);
		if (len > 0 && data->file[i][len - 1] == '\n')
			len--;
		data->map->height++;
		if (len > data->map->width)
			data->map->width = len;
		i++;
	}
	return (data->map->height > 0 && data->map->width > 0);
}
