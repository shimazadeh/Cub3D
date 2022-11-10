/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:56:14 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/08 17:09:36 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub3D(t_cub *cub)
{
	t_hit	hit[1];

	init_hit_struct(hit);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->width, cub->height, "lol");
	if (!cub->win_ptr)
	{
		ft_putstr_fd("Error\nWindow could not be created!\n", 2);
		return ;
	}
	mlx_hook(cub->win_ptr, 2, 1L<<0, &key_hook, cub);
	mlx_hook(cub->win_ptr, 33, 131072, &ft_exit, cub);
	mlx_loop_hook(cub->mlx_ptr, &handle_no_event, NULL);
	mlx_loop(cub->mlx_ptr);
	while (1)
		cub3D_render_pos(cub, hit);
}

void	cub3D_render_pos(t_cub *cub, t_hit *hit)
{
	int		i;
	int 	ray_angle;

	ray_angle = FOV_angle / NUM_RAYS;

	i = 0;
	while (i)
	{
		get_cur_angle(cub, i);
		init_hit_struct(hit);
		get_next_hitpoint(cub, hit);
		// 3. from those coordinates, get the perpendicular wall distance
		// 4. from this distance, draw the correct ratioed vertical line
		i--;
	}
}

void	get_cur_angle(t_cub *cub, int i)//need to double check if radians or degrees
{
	cub->cur_angle = (cub->base_angle + ((cub->width - i) / cub->width) * 66);
	if (cub->cur_angle > 360)
		cub->cur_angle -= 360;
	else if (cub->cur_angle < 0)
		cub->cur_angle += 360;

}

void	get_next_hitpoint(t_cub *cub, t_hit *hit)
{
	set_ray_direction(cub);
	check_horizontal_hit(hit, cub);
	check_vertical_hit(hit, cub);
	select_shortest_hitpoint(hit, cub);
}

void	get_initial_vhit(t_hit *hit, t_cub *cub)
{
	double	delta_x;

	hit->v_hitX = floor(cub->posx / 32) * 32;
	if (cub->right)
		hit->h_hitX += 32;
	delta_x = cub->posX - hit->v_hitX;
	hit->v_hitX = delta_x;
	hit->v_hitY = cub->posY + (-delta_x * tan(cub->base_angle));
}

void	check_vertical_hit(t_hit *hit, t_cub *cub)
{
	double	x_step;
	double	y_step;

	x_step = 32;
	y_step = 32 * tan(cub->cur_angle);

	if ((cub->left && x_step > 0) || (cub->right && x_step < 0))
		x_step *= -1;

	if ((cub->down && y_step > 0) || (cub->up && y_step < 0))
		y_step *= -1;

	get_initial_vhit(hit, cub);

	while(!check_if_hit(hit->v_hitX, hit->v_hitY, cub->map))
	{
		hit->v_hitX += x_step;
		hit->v_hitY += y_step;
	}
}

void	get_initial_hhit(t_hit *hit, t_cub *cub)/
{
	double	delta_y;

	hit->h_hitY = floor(cub->posY / 32) * 32;//need to figure out the floor func
	if (cub->down)
		hit->h_hitY += 32;
	delta_y = cub->posY - hit->h_hitY;
	hit->h_hitY = delta_y;
	hit->h_hitX = cub->posX + delta_y / tan(cub->base_angle);
}

void	check_horizontal_hit(t_hit *hit, t_cub *cub)
{
	double	x_step;
	double	y_step;

	x_step = 32 / tan(cub->cur_angle); //32 is the tile size??
	y_step = 32;

	if ((cub->left && x_step > 0) || (cub->right && x_step < 0))
		x_step *= -1;

	if ((cub->down && y_step > 0) || (cub->up && y_step < 0))
		y_step *= -1;

	get_initial_hhit(hit, cub);

	while(!check_if_hit(hit->h_hitX, hit->h_hitY, cub->map))
	{
		hit->h_hitX += x_step;
		hit->h_hitY += y_step;
	}
}

int	check_if_hit(double x, double y, char **map)
{
	//convert x and y to i and j of map???
	if (map[i][j] == "1")
		return 1;
	return 0;
}

void	select_shortest_hitpoint(t_hit *hit, t_cub *cub)
{
	double	h_distance;
	double	v_distance;

	h_distance = calculate_distance(hit->h_hitX, cub->posX, hit->h_hitY, cub->posY);
	v_distance = calculate_distance(hit->v_hitX, cub->posX, hit->v_hitY, cub->posY);

	if (v_distance < h_distance)
	{
		cub->hitX = hit->v_hitX;
		cub->hitY = hit->v_hitY;
		cub->hit_vertical = true;
	}
	else
	{
		cub->hit_vertical = false;
		cub->hitX = hit->h_hitX;
		cub->hitY = hit->h_hitY;
	}
}

void	set_ray_direction(t_cub *cub)
{
	if(cub->ray_angle > 0 && cub->ray_angle < 180)
		cub->up = true;
	else
		cub->down = true;

	if (cub->ray_angle > 270 || cub->ray_angle < 90)
		cub->right = true;
	else
		cub->left = true;
}

double	calculate_distance(double x1, double x2, double y1, double y2)
{
	double	distance;

	distance = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	return (distance);
}
