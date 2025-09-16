/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:12:41 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 19:01:47 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_id	*create_new_id(t_data *data, char **splitted)
{
	t_id	*new_id;

	if (!splitted || !splitted[0] || !splitted[1])
		return (NULL);
	new_id = ft_my_malloc(data->allocator, sizeof(t_id));
	if (!new_id)
		return (NULL);
	new_id->key = ft_my_strdup(data->allocator, splitted[0]);
	new_id->value = ft_my_strdup(data->allocator, splitted[1]);
	if (!new_id->key || !new_id->value)
	{
		ft_my_free(data->allocator, new_id->key);
		ft_my_free(data->allocator, new_id->value);
		ft_my_free(data->allocator, new_id);
		return (NULL);
	}
	new_id->next = NULL;
	ft_my_free_splitted(data->allocator, splitted);
	return (new_id);
}

char	**parse_line_to_tokens(t_data *data, char *line)
{
	int		i;
	char	**splitted;
	int		len;

	if (!line)
		return (NULL);
	if (line[0] == '\n' || line[0] == '\0')
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	splitted = ft_split_alloc(data->allocator, line + i, ' ');
	if (!splitted || !splitted[0] || !splitted[1])
	{
		if (splitted)
			ft_my_free_splitted(data->allocator, splitted);
		return (NULL);
	}
	return (splitted);
}

int	process_id_line(t_data *data, char *line)
{
	char	**splitted;
	t_id	*new_id;

	splitted = parse_line_to_tokens(data, line);
	if (!splitted)
		return (1);
	new_id = create_new_id(data, splitted);
	if (!new_id)
		return (ft_my_free_splitted(data->allocator, splitted), 0);
	new_id->next = data->ids;
	data->ids = new_id;
	return (1);
}

int	process_config_lines(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !is_map_line(line))
	{
		if (!process_id_line(data, line))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (line && is_map_line(line))
	{
		if (!data->map)
			return (free(line), 0);
		data->map->height = 0;
		data->map->width = 0;
		if (!count_map_dimensions(data, line, fd))
			return (free(line), 0);
	}
	return (1);
}

int	load_file(char *filename, t_data *data)
{
	int		fd;

	if (!filename || !data || !data->allocator)
		return (ft_printf("Error: load_file - invalid parameters\n"), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: load_file - %s\n", filename), 0);
	if (!process_config_lines(data, fd))
	{
		close(fd);
		return (ft_printf("Error: load_file - processing failed\n"), 0);
	}
	close(fd);
	return (1);
}
