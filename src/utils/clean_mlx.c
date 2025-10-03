/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:28:19 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/03 13:28:27 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	destroy_texture_images(t_data *data)
{
	if (!data || !data->textures)
		return ;
	if (data->textures->north_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->north_img.img);
	if (data->textures->south_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->south_img.img);
	if (data->textures->west_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->west_img.img);
	if (data->textures->east_img.img)
		mlx_destroy_image(data->mlx->mlx_ptr, data->textures->east_img.img);
}

int	end_display(t_data *data)
{
	if (!data)
		exit(0);
	if (data->mlx)
	{
		destroy_texture_images(data);
		if (data->mlx->img && data->mlx->img->img)
			mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img->img);
		if (data->mlx->win_ptr)
			mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
		if (data->mlx->mlx_ptr)
		{
			mlx_destroy_display(data->mlx->mlx_ptr);
			free(data->mlx->mlx_ptr);
		}
		if (data->mlx->img)
			ft_my_free(data->allocator, data->mlx->img);
		ft_my_free(data->allocator, data->mlx);
	}
	clean_data(data);
	exit(0);
	return (0);
}
