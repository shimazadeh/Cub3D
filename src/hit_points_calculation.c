#include "cub3D.h"

void	update_data(t_hit *hit, t_cub *cub)
{
	if (hit->v_hit)
	{
		cub->hitX = hit->v_hitX;
		cub->hitY = hit->v_hitY;
		cub->prev_text = cub->cur_text;
		cub->cur_text = hit->v_text;

	}
	else
	{
		cub->hitX = hit->h_hitX;
		cub->hitY = hit->h_hitY;
		cub->prev_text = cub->cur_text;
		cub->cur_text = hit->h_text;
	}
}

void	get_initial_vhit(t_hit *hit, t_cub *cub)
{
	double	delta_x;

	hit->v_hitX = floor(cub->posX);
	if (cub->right)
		hit->h_hitX += 1;
	delta_x = cub->posX - hit->v_hitX;
	// hit->v_hitX = delta_x;
	hit->v_hitY = cub->posY + (-delta_x * tan(cub->base_angle * M_PI / 180));
	check_if_hit_v(hit, cub);
}

void	get_initial_hhit(t_hit *hit, t_cub *cub)
{
	double	delta_y;

	hit->h_hitY = floor(cub->posY);//need to figure out the floor func
	if (cub->down)
		hit->h_hitY += 1;
	delta_y = cub->posY - hit->h_hitY;
	// hit->h_hitY = delta_y;
	hit->h_hitX = cub->posX + delta_y / tan(cub->base_angle * (M_PI / 180));
	// printf("deltay is %f, posx %f, poxY %f\n", delta_y, cub->posX, cub->posY);
	check_if_hit_h(hit, cub);
}

void	check_if_hit_h(t_hit *hit, t_cub *cub)
{
	int		i;
	int		j;
	int		text;

	j = hit->h_hitX;
	i = 0;
	text = 0;
	if (cub->up)
	{
		i = hit->h_hitY - 1;
		text = 'n';
	}
	else
	{
		i = hit->h_hitY;
		text = 's';
	}
	if (i >= 0 && i <= cub->maph && j >= 0 && j <= cub->mapw)
	{
		printf("i is %d, j is %d\n", i, j);
		if (cub->map[i][j] == '1')
		{
			hit->h_hit = 1;
			hit->h_text = text;
		}
	}
}

void	check_if_hit_v(t_hit *hit, t_cub *cub)
{
	int		i;
	int		j;
	int		text;

	i = hit->v_hitY;
	j = 0;
	text = 0;
	if (cub->left)
	{
		j = hit->v_hitX - 1;
		text = 'w';
	}
	else
	{
		j = hit->v_hitX;
		text = 'e';
	}
	if (i >= 0 && i < cub->maph && j >= 0 && j < cub->mapw)
	{
		printf("i is %d, j is %d\n", i, j);
		if (cub->map[i][j] == '1')
		{
			hit->v_hit = 1;
			hit->v_text = text;
		}
	}
}

void	select_shortest_hitpoint(t_hit *hit, t_cub *cub)
{
	double	h_distance;
	double	v_distance;

	h_distance = 0;
	v_distance = 0;
	if (hit->h_hit)
	{
		h_distance = calculate_distance(hit->h_hitX, cub->posX, hit->h_hitY, cub->posY);
		// printf("horizontal hit with %f\n", h_distance);
	}
	if (hit->v_hit)
	{
		v_distance = calculate_distance(hit->v_hitX, cub->posX, hit->v_hitY, cub->posY);
		// printf("vertical hit with %f\n", v_distance);
	}
	if (hit->v_hit && hit->h_hit)
	{
		if (v_distance < h_distance)
			hit->h_hit = false;
		else
			hit->v_hit = false;
	}
	if (hit->v_hit)
		cub->dist = v_distance;
	else
		cub->dist = h_distance;
}

double	calculate_distance(double x1, double x2, double y1, double y2)
{
	double	distance;

	distance = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	return (distance);
}

// void	check_vertical_hit(t_hit *hit, t_cub *cub)
// {
// 	double	x_step;
// 	double	y_step;

// 	x_step = 1;
// 	y_step = tan(cub->cur_angle);

// 	if ((cub->left && x_step > 0) || (cub->right && x_step < 0))
// 		x_step *= -1;

// 	if ((cub->down && y_step > 0) || (cub->up && y_step < 0))
// 		y_step *= -1;

// 	get_initial_vhit(hit, cub);

// 	while(!check_if_hit(hit, cub, 1))
// 	{
// 		hit->v_hitX += x_step;
// 		hit->v_hitY += y_step;
// 	}
// }

// void	check_horizontal_hit(t_hit *hit, t_cub *cub)
// {
// 	double	x_step;
// 	double	y_step;

// 	x_step = 1 / tan(cub->cur_angle); //1 is the tile size
// 	y_step = 1;

// 	if ((cub->left && x_step > 0) || (cub->right && x_step < 0))
// 		x_step *= -1;

// 	if ((cub->down && y_step > 0) || (cub->up && y_step < 0))
// 		y_step *= -1;

// 	get_initial_hhit(hit, cub);

// 	while(!check_if_hit(hit, cub, 0))
// 	{
// 		hit->h_hitX += x_step;
// 		hit->h_hitY += y_step;
// 	}
// }
