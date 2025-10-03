#include "cub3D.h"

void    render_3d_scene(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < data->mlx->width)
	{
		init_ray(&ray, data, x);		// setup rayon
		perform_dda(&ray, data);		// avance jusqu’à mur
		compute_wall(&ray, data);		// calcule distance / hauteur
		draw_column(&ray, data, x);		// trace mur dans la colonne x
		x++;
	}
	mlx_put_image_to_window(data->mlx->mlx_ptr,
							data->mlx->win_ptr,
							data->mlx->img->img, 0, 0);
	render_map2d(data, 8); // affichage de la map 2D en haut a gauche
}

void    init_ray(t_ray *ray, t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)data->mlx->width - 1; // définit la colonne sur laquelle on travaille dans une plage de [-1, 1]
	// -1 = la colonne tout à gauche et 1 la colonne tout à droite
	ray->ray_dir_x = data->player->dir_x + data->player->plane_x * ray->camera_x;
	ray->ray_dir_y = data->player->dir_y + data->player->plane_y * ray->camera_x;
	// dir_x et dir_y donnent un vecteur de direction qui pointent vers le centre de l'écran.
	// ce calcul permet d'obtenir la direction (sous forme d'un vecteur [ray_dir_x, ray_dir_y]) vers laquel va le rayon;
	ray->map_x = (int)data->player->x;
	ray->map_y = (int)data->player->y;
	// Donne la position de départ du joueur, on caste en int pour avoir l'indice : 111 (0,0; 1,0; 2,0)
	//																				101	(0,1; 11; 2,1)
	//																				111	(0,2; 1,2; 2,2)
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = DBL_MAX; // si le rayon qui est parfaitement vertical
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x); // correspond a la distance entre chaque ligne vertical

	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = DBL_MAX; // si le rayon qui est parfaitement horizontal
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y); // correspond a la distance entre chaque ligne horizontal

	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;	// si la direction du rayon sur l'axe x est négatif le rayon va vers la gauche
		ray->side_dist_x = (data->player->x - ray->map_x) * ray->delta_dist_x; // correspond a la distance entre le personnage et la première ligne vertical
	}
	else
	{
		ray->step_x = 1;	// si la direction du rayon sur l'axe x est positif le rayon va vers la droite
		ray->side_dist_x = (ray->map_x + 1.0 - data->player->x) * ray->delta_dist_x; // correspond a la distance entre le personnage et la première ligne vertical
	}

	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1; // si la direction du rayon sur l'axe y est négatif le rayon va vers le haut
		ray->side_dist_y = (data->player->y - ray->map_y) * ray->delta_dist_y; // correspond a la distance entre le personnage et la première ligne horizontal
	}
	else
	{
		ray->step_y = 1; // si la direction du rayon sur l'axe y est positif le rayon va vers le bas
		ray->side_dist_y = (ray->map_y + 1.0 - data->player->y) * ray->delta_dist_y;
	}
	ray->hit = 0;
	ray->wall_rgb = 0x000000;
}

void    perform_dda(t_ray *ray, t_data *data)
{
	while (!ray->hit) // tant que le rayon n'as pas touché de mur hit = 0
	{
		if (ray->side_dist_x < ray->side_dist_y) // içi on détermine quel mur vas être touché en premier (l'horizontal ou le vertical)
		{
			ray->side_dist_x += ray->delta_dist_x;
			// içi on ajoute la distance jusqu'a la prochaine ligne vertical + la distance entre chaque ligne vertical;
			ray->map_x += ray->step_x;
			// on fait avancer le rayon sur une case sur la gauche ou sur la droite
			ray->side = 0;
			// permet de savoir quel mur a été touché
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map->grid[ray->map_y][ray->map_x] == '1') // si on touche un mur on arrête de faire avancer le rayon
			ray->hit = 1;
	}
}

void    compute_wall(t_ray *ray, t_data *data)
{
	if (ray->side == 0) // si le mur touché est sur l'axe vertical
	{
		if (ray->ray_dir_x > 0)
        	ray->wall_rgb = 0xFF0000;
		else
        	ray->wall_rgb = 0x00FF00;
		ray->perp_wall_dist = (ray->map_x - data->player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
		//  calcule la distance perpendiculaire entre le player et le mur (permet de corriger l'effet fisheye)
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->wall_rgb = 0x0000FF;
		else
			ray->wall_rgb = 0xFFFF00;
		ray->perp_wall_dist = (ray->map_y - data->player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
	ray->line_height = (int)(data->mlx->height / ray->perp_wall_dist);
	// permet de calculer la hauteur du mur en fonction de ça distance
	ray->draw_start = -ray->line_height / 2 + data->mlx->height / 2;
	// permet de savoir sur l'axe vertical ou on commence a imprimer le mur
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	// si on est proche du mur son affichage peut être négatif car il dépasse la taille de la fenêtre donc on le set à 0
	ray->draw_end = ray->line_height / 2 + data->mlx->height / 2;
	// correspond sur l'axe Y le dernier endroit au le mur doit s'afficher
	if (ray->draw_end >= data->mlx->height)
		ray->draw_end = data->mlx->height - 1;
	// s'il dépasse la taille de la fenêtre on le met sur le dernier pixel valide (si 400px draw_end = 400 - 1)
}
