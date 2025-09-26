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
}

void    init_ray(t_ray *ray, t_data *data, int x)
{
	ray->cameraX = 2 * x / (double)data->mlx->width - 1; // définit la colonne sur laquelle on travaille dans une plage de [-1, 1]
	// -1 = la colonne tout à gauche et 1 la colonne tout à droite
	ray->rayDirX = data->player->dirX + data->player->planeX * ray->cameraX;
	ray->rayDirY = data->player->dirY + data->player->planeY * ray->cameraX;
	// dirX et dirY donnent un vecteur de direction qui pointent vers le centre de l'écran.
	// ce calcul permet d'obtenir la direction (sous forme d'un vecteur [rayDirX, rayDirY]) vers laquel va le rayon;
	ray->mapX = (int)data->player->x;
	ray->mapY = (int)data->player->y;
	// Donne la position de départ du joueur, on caste en int pour avoir l'indice : 111 (0,0; 1,0; 2,0)
	//																				101	(0,1; 11; 2,1)
	//																				111	(0,2; 1,2; 2,2)
	if (ray->rayDirX == 0)
		ray->deltaDistX = DBL_MAX; // si le rayon qui est parfaitement vertical
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX); // correspond a la distance entre chaque ligne vertical

	if (ray->rayDirY == 0)
		ray->deltaDistY = DBL_MAX; // si le rayon qui est parfaitement horizontal
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY); // correspond a la distance entre chaque ligne horizontal

	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;	// si la direction du rayon sur l'axe x est négatif le rayon va vers la gauche
		ray->sideDistX = (data->player->x - ray->mapX) * ray->deltaDistX; // correspond a la distance entre le personnage et la première ligne vertical
	}
	else
	{
		ray->stepX = 1;	// si la direction du rayon sur l'axe x est positif le rayon va vers la droite
		ray->sideDistX = (ray->mapX + 1.0 - data->player->x) * ray->deltaDistX; // correspond a la distance entre le personnage et la première ligne vertical
	}

	if (ray->rayDirY < 0)
	{
		ray->stepY = -1; // si la direction du rayon sur l'axe y est négatif le rayon va vers le haut
		ray->sideDistY = (data->player->y - ray->mapY) * ray->deltaDistY; // correspond a la distance entre le personnage et la première ligne horizontal
	}
	else
	{
		ray->stepY = 1; // si la direction du rayon sur l'axe y est positif le rayon va vers le bas
		ray->sideDistY = (ray->mapY + 1.0 - data->player->y) * ray->deltaDistY;
	}
	ray->hit = 0;
	ray->wall_rgb = 0x000000;
}

void    perform_dda(t_ray *ray, t_data *data)
{
	while (!ray->hit) // tant que le rayon n'as pas touché de mur hit = 0
	{
		if (ray->sideDistX < ray->sideDistY) // içi on détermine quel mur vas être touché en premier (l'horizontal ou le vertical)
		{
			ray->sideDistX += ray->deltaDistX;
			// içi on ajoute la distance jusqu'a la prochaine ligne vertical + la distance entre chaque ligne vertical;
			ray->mapX += ray->stepX;
			// on fait avancer le rayon sur une case sur la gauche ou sur la droite
			ray->side = 0;
			// permet de savoir quel mur a été touché
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (data->map->grid[ray->mapY][ray->mapX] == '1') // si on touche un mur on arrête de faire avancer le rayon
			ray->hit = 1;
	}
}

void    compute_wall(t_ray *ray, t_data *data)
{
	if (ray->side == 0) // si le mur touché est sur l'axe vertical
	{
		if (ray->rayDirX > 0)
        	ray->wall_rgb = 0xFF0000;
		else
        	ray->wall_rgb = 0x00FF00;
		ray->perpWallDist = (ray->mapX - data->player->x + (1 - ray->stepX) / 2) / ray->rayDirX;
		//  calcule la distance perpendiculaire entre le player et le mur (permet de corriger l'effet fisheye)
	}
	else
	{
		if (ray->rayDirY > 0)
        	ray->wall_rgb = 0x0000FF;
		else
        	ray->wall_rgb = 0xFFFF00;
		ray->perpWallDist = (ray->mapY - data->player->y + (1 - ray->stepY) / 2) / ray->rayDirY;
	}
	ray->lineHeight = (int)(data->mlx->height / ray->perpWallDist);
	// permet de calculer la hauteur du mur en fonction de ça distance
	ray->drawStart = -ray->lineHeight / 2 + data->mlx->height / 2;
	// permet de savoir sur l'axe vertical ou on commence a imprimer le mur
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	// si on est proche du mur son affichage peut être négatif car il dépasse la taille de la fenêtre donc on le set à 0
	ray->drawEnd = ray->lineHeight / 2 + data->mlx->height / 2;
	// correspond sur l'axe Y le dernier endroit au le mur doit s'afficher
	if (ray->drawEnd >= data->mlx->height)
		ray->drawEnd = data->mlx->height - 1;
	// s'il dépasse la taille de la fenêtre on le met sur le dernier pixel valide (si 400px drawEnd = 400 - 1)
}

void    draw_column(t_ray *ray, t_data *data, int x)
{
	int	y;
	int	ceiling_rgb;
	int	floor_rgb;

	floor_rgb = create_rgb(data->textures->floor_color->r,
								 data->textures->floor_color->g,
								 data->textures->floor_color->b);
	ceiling_rgb = create_rgb(data->textures->ceiling_color->r,
								 data->textures->ceiling_color->g,
								 data->textures->ceiling_color->b);
	y = 0;
	while (y < ray->drawStart)
	{
		put_pixel(data->mlx->img, x, y, ceiling_rgb);
		y++;
	}
	while (y <= ray->drawEnd)
	{
		put_pixel(data->mlx->img, x, y, ray->wall_rgb);
		y++;
	}
	while (y < data->mlx->height)
	{
		put_pixel(data->mlx->img, x, y, floor_rgb);
		y++;
	}
}
