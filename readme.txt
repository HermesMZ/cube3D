pour les mallocs :
utiliser les fonctions ft_my_malloc et ft_my_free
il faut juste mettre en premier argument data->allocator, le deuxieme est comme les fonctions de base.
Ex :
data->textures->ceiling_color = ft_my_malloc(data->allocator, sizeof(t_color));
ft_my_free(data->allocator, map);

Structure principale s_data :
tout les ids qu'il peut y avoir dans le fichier sont stockés dans une liste chaînée
	* key
	* value
	* next
les textures et couleurs sont stockées dans une structure t_textures *textures
	* N S E W
	* plafond sol
la map est stockée dans une structure t_map *map :
	* grid : tableau 2D de char
	* width : largeur de la map (nombre de colonnes)
	* height : hauteur de la map (nombre de lignes)
le joueur est stocké dans une structure t_player *player :
	* position : tableau de 2 int (x et y)
	* direction : char ('N', 'S', 'E', 'W')
la structure t_keys qui va gerer les touches avec les keyhooks.

la gestion de la fenêtre et de la bibliothèque graphique est commentée pour l'instant
	j'ai copie colle celles que j'avais faites pour fdf pour l'instant

et l'allocator pour stocker tout les my_alloc et pouvoir tous les free a la fin.


Sinon, les fonctions clean sont ok pour l'instant. Il faudra peut-etre les modifier une fois qu'on
aura implemente la partie graphique.

Quelques fonctions de debug.
Je les appelle pour l'instant dans le main pour voir le resultat du parsing.


 make && valgrind ./cub3D subject.cub 

 pour tester.