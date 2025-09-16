/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:01:07 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 18:48:05 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_texture_id(t_mandatory_ids *ids, char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0)
	{
		if (ids->north_texture)
			return (ft_printf("Error - Duplicate north texture\n"), 0);
		ids->north_texture = true;
	}
	if (ft_strncmp(id, "SO", 2) == 0)
	{
		if (ids->south_texture)
			return (ft_printf("Error - Duplicate south texture\n"), 0);
		ids->south_texture = true;
	}
	if (ft_strncmp(id, "WE", 2) == 0)
	{
		if (ids->west_texture)
			return (ft_printf("Error - Duplicate west texture\n"), 0);
		ids->west_texture = true;
	}
	if (ft_strncmp(id, "EA", 2) == 0)
	{
		if (ids->east_texture)
			return (ft_printf("Error - Duplicate east texture\n"), 0);
		ids->east_texture = true;
	}
	return (1);
}

int	check_color_id(t_mandatory_ids *ids, char *id)
{
	if (ft_strncmp(id, "F", 1) == 0 && ft_strlen(id) == 1)
	{
		if (ids->floor_color)
			return (ft_printf("Error - Duplicate floor color\n"), 0);
		ids->floor_color = true;
	}
	if (ft_strncmp(id, "C", 1) == 0 && ft_strlen(id) == 1)
	{
		if (ids->ceiling_color)
			return (ft_printf("Error - Duplicate ceiling color\n"), 0);
		ids->ceiling_color = true;
	}
	return (1);
}

int	textures_present(t_mandatory_ids *mandatory_ids, t_id *ids)
{
	t_id	*current;

	if (!ids)
		return (0);
	current = ids;
	while (current)
	{
		if (!check_texture_id(mandatory_ids, current->key))
			return (0);
		if (!check_color_id(mandatory_ids, current->key))
			return (0);
		current = current->next;
	}
	return (1);
}

int	mandatory_ids_present(t_id *ids)
{
	t_mandatory_ids	mandatory_ids;

	if (!ids)
		return (0);
	mandatory_ids = (t_mandatory_ids){false};
	if (!textures_present(&mandatory_ids, ids))
		return (0);
	if (!mandatory_ids.north_texture || !mandatory_ids.south_texture
		|| !mandatory_ids.west_texture || !mandatory_ids.east_texture
		|| !mandatory_ids.floor_color || !mandatory_ids.ceiling_color)
	{
		ft_printf("Missing: NO=%d SO=%d WE=%d EA=%d F=%d C=%d\n",
			mandatory_ids.north_texture, mandatory_ids.south_texture,
			mandatory_ids.west_texture, mandatory_ids.east_texture,
			mandatory_ids.floor_color, mandatory_ids.ceiling_color);
		ft_printf("Error - Missing mandatory identifiers\n");
		return (0);
	}
	return (1);
}

int	check_input(t_data *data, char *filename)
{
	if (!data || !filename)
		return (0);
	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".cub", 4) != 0)
		return (ft_printf("Error - File must have a .cub extension\n"), 0);
	if (!parse_file(filename, &data))
		return (0);
	if (!mandatory_ids_present(data->ids))
		return (0);
	return (1);
}
