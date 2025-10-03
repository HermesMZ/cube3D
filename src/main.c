/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:42:48 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/03 16:52:51 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Penser à retester les leaks sans le script run.sh

// debug_print_data(data);

int	main(int argc, char **argv)
{
	t_data		*data;
	t_lalloc	*allocator;

	if (argc != 2)
		return (printf("Error: Usage: ./cub3D <map_file.cub>\n"), 1);
	allocator = ft_init_allocator();
	if (!allocator)
		return (printf("Error: Failed to initialize allocator\n"), 1);
	if (!init_data(&data, allocator))
		return (printf("Error: Failed to initialize data\n"), 1);
	if (!check_input(data, argv[1]))
		return (printf("Error: Invalid input\n"), end_display(data), 1);
	if (!load_all_textures(data))
		return (printf("Error: Failed to load textures\n"),
			end_display(data), 1);
	mlx_mouse_hide(data->mlx->mlx_ptr, data->mlx->win_ptr);
	mlx_mouse_move(data->mlx->mlx_ptr, data->mlx->win_ptr, W / 2, H / 2);
	mlx_loop_hook(data->mlx->mlx_ptr, update, data);
	mlx_hook(data->mlx->win_ptr, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->mlx->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->mlx->win_ptr, 17, 0, end_display, data);
	mlx_loop(data->mlx->mlx_ptr);
	return (0);
}
