/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:12:41 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:40:01 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	fill_data_file(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		i;
	int		len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		data->file[i] = ft_my_strdup(data->allocator, line);
		if (!data->file[i])
			return (free(line), close(fd), 0);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data->file[i] = NULL;
	close(fd);
	return (1);
}

// Fonction pour charger tout le fichier dans data->file
int	load_file(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		line_count;

	if (!filename || !data || !data->allocator)
	{
		ft_printf("Error: load_file - invalid parameters\n");
		return (0);
	}
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: load_file - cannot open file %s\n", filename);
		return (0);
	}
	
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	
	ft_printf("load_file: found %d lines\n", line_count);
	
	data->file = ft_my_malloc(data->allocator, sizeof(char *)
			* (line_count + 1));
	if (!data->file)
	{
		ft_printf("Error: load_file - failed to allocate data->file\n");
		return (0);
	}
	
	if (!fill_data_file(filename, data))
	{
		ft_printf("Error: load_file - failed to fill data->file\n");
		return (0);
	}
	
	ft_printf("load_file: successfully loaded file\n");
	return (1);
}
