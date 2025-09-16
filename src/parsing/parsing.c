/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:45:13 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Fonction pour extraire les couleurs RGB d'une ligne
t_color	*extract_rgb(t_data *data, t_color *color, char *line)
{
	if (!line || !color)
	{
		ft_printf("extract_rgb: line or color is NULL\n");
		return (ft_my_free(data->allocator, color), NULL);
	}
	color->r = 0;
	color->g = 0;
	color->b = 0;
	while (*line && !ft_isdigit(*line))
		line++;
	while (*line && ft_isdigit(*line))
		color->r = color->r * 10 + (*line++ - '0');
	while (*line && !ft_isdigit(*line))
		line++;
	while (*line && ft_isdigit(*line))
		color->g = color->g * 10 + (*line++ - '0');
	while (*line && !ft_isdigit(*line))
		line++;
	while (*line && ft_isdigit(*line))
		color->b = color->b * 10 + (*line++ - '0');
	return (color);
}

// Fonction pour chercher une texture spécifique dans le fichier
char	*find_texture(t_data *data, char *identifier)
{
	int		i;

	if (!data->file || !identifier)
		return (NULL);
	i = 0;
	while (data->file[i])
	{
		if (data->file[i][0] == identifier[0])
			return (ft_my_strdup(data->allocator, data->file[i] + 2));
		i++;
	}
	return (NULL);
}

// Fonction pour chercher une couleur spécifique dans le fichier
t_color	*find_color(t_data *data, char *identifier)
{
	int		i;
	t_color	*color;

	if (!data->file || !identifier)
		return (NULL);
	i = 0;
	while (data->file[i])
	{
		if (data->file[i][0] == identifier[0])
		{
			color = ft_my_malloc(data->allocator, sizeof(t_color));
			if (!color)
				return (NULL);
			return (extract_rgb(data, color, data->file[i]));
		}
		i++;
	}
	return (NULL);
}

// Fonction pour parser les textures depuis data->file
int	parse_textures(t_data *data)
{
	if (!data || !data->textures)
		return (0);
	data->textures->north_texture = find_texture(data, "N");
	data->textures->south_texture = find_texture(data, "S");
	data->textures->west_texture = find_texture(data, "W");
	data->textures->east_texture = find_texture(data, "E");
	data->textures->floor_color = find_color(data, "F");
	data->textures->ceiling_color = find_color(data, "C");
	return (1);
}

// Fonction principale de parsing
int	parse_file(char *filename, t_data **data)
{
	if (!load_file(filename, *data))
		return (ft_printf("Error: Failed to load file\n"), 0);
	if (!parse_textures(*data))
		return (ft_printf("Error: Failed to parse textures\n"), 0);
	if (!parse_map_from_file(data))
		return (ft_printf("Error: Failed to parse map\n"), 0);
	return (1);
}
