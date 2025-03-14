#include "cub3d.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Définition d'une petite map 2D (1 = mur, 0 = vide)
int			worldMap[MAP_WIDTH][MAP_HEIGHT] = {{1, 1, 1, 1, 1, 1, 1, 1}, {1, 0,
				0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 1,
				0, 1}, {1, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1}};

// Structure pour gérer la MLX et les données du joueur
typedef struct s_data
{
	void	*mlx;
	void	*win;
	double posX, posY;     // Position du joueur
	double dirX, dirY;     // Direction du regard
	double planeX, planeY; // Plan de la caméra
}			t_data;

// Fonction pour tracer une ligne verticale (mur)
void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	for (int y = start; y < end; y++)
		mlx_pixel_put(data->mlx, data->win, x, y, color);
}

// Fonction principale du raycasting (DDA)
void	raycasting(t_data *data)
{
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		hit;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIN_WIDTH - 1; // Convertir x en [-1,1]
		rayDirX = data->dirX + data->planeX * cameraX;
		rayDirY = data->dirY + data->planeY * cameraX;
		mapX = (int)data->posX;
		mapY = (int)data->posY;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		double sideDistX, sideDistY;
		int stepX, stepY;
		int hit = 0, side;
		// Calcul du step et de la distance initiale jusqu'au premier mur
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}
		// Lancement de l'algorithme DDA pour trouver le mur
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0; // Mur vertical
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1; // Mur horizontal
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		// Calcul de la distance au mur
		perpWallDist = (side == 0) ? (mapX - data->posX + (1 - stepX) / 2)
			/ rayDirX : (mapY - data->posY + (1 - stepY) / 2) / rayDirY;
		// Calcul de la hauteur de la ligne à dessiner
		lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;
		// Choix de la couleur
		int color = (side == 0) ? 0xFF0000 : 0x770000;
			// Rouge plus sombre pour les côtés
		// Dessiner le mur
		draw_vertical_line(data, x, drawStart, drawEnd, color);
	}
}

// Fonction pour gérer la fermeture avec "Échap"
int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{ // Touche ESC
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

// Fonction principale
int	main(void)
{
	t_data	data;

	// Initialisation de la MLX
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Raycasting avec MLX");
	// Initialisation du joueur
	data.posX = 2.0;
	data.posY = 2.0;
	data.dirX = 1.0;
	data.dirY = 0.0;
	data.planeX = 0.0;
	data.planeY = 0.66; // Détermine le champ de vision (FOV)
	// Exécuter le raycasting et afficher les murs
	raycasting(&data);
	// Gérer les touches (fermeture avec Échap)
	mlx_key_hook(data.win, key_hook, &data);
	// Lancement de la boucle MLX
	mlx_loop(data.mlx);
	return (0);
}
