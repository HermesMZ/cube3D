/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:42:48 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 11:11:50 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	t_lalloc	*allocator;

	ft_printf("Hello, Cube3D!\n");
	if (argc != 2)
		return (ft_printf("Error - Usage: ./cub3D <map_file.cub>\n"), 1);
	allocator = ft_init_allocator();
	if (!allocator)
		return (ft_printf("Error - Failed to initialize allocator\n"), 1);
	if (!init_data(&data, allocator))
		return (ft_printf("Error - Failed to initialize data\n"), 1);
	if (!check_input(data, argv[1]))
		return (1);
	debug_print_data(data);
	clean_data(data);
	ft_printf("Goodbye, Cube3D!\n");
	return (0);
}
