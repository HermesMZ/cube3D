/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:40:01 by mzimeris         ###   ########.fr       */
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
		if (data->file[i][0] == identifier[0] && data->file[i][1] == ' ')
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
		if (data->file[i][0] == identifier[0] && data->file[i][1] == ' ')
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

// Fonction pour allouer le grid de la carte
int	allocate_map_grid(t_data *data)
{
	int	i;

	if (data->map->height <= 0 || data->map->width <= 0)
		return (0);
	data->map->grid = ft_my_malloc(data->allocator,
			sizeof(char *) * (data->map->height + 1));
	if (!data->map->grid)
		return (0);
	i = 0;
	while (i < data->map->height)
	{
		data->map->grid[i] = ft_my_malloc(data->allocator,
				data->map->width + 1);
		if (!data->map->grid[i])
			return (0);
		ft_memset(data->map->grid[i], ' ', data->map->width);
		data->map->grid[i][data->map->width] = '\0';
		i++;
	}
	data->map->grid[data->map->height] = NULL;
	return (1);
}

// Fonction pour remplir la carte avec les données du fichier
int	fill_map_from_file(t_data *data)
{
	int	start;
	int	i;
	int	row;
	int	j;
	int	len;

	start = find_map_start(data);
	if (start == -1)
		return (0);
	row = 0;
	i = start;
	while (data->file[i] && is_map_line(data->file[i]) && row < data->map->height)
	{
		len = ft_strlen(data->file[i]);
		if (len > 0 && data->file[i][len - 1] == '\n')
			len--;
		j = 0;
		while (j < len && j < data->map->width)
		{
			data->map->grid[row][j] = data->file[i][j];
			j++;
		}
		row++;
		i++;
	}
	return (1);
}

// Fonction pour parser la carte depuis data->file
int	parse_map_from_file(t_data **data)
{
	if (!count_map_dimensions(*data))
		return (0);
	if (!allocate_map_grid(*data))
		return (0);
	if (!fill_map_from_file(*data))
		return (0);
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
