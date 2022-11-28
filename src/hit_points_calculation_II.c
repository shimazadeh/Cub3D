/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_points_calculation_II.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:33:07 by shabibol          #+#    #+#             */
/*   Updated: 2022/11/28 17:33:08 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_next_hitpoint(t_cub *cub, t_hit *hit)
{
	get_horizontal_hit(cub, hit);
	get_vertical_hit(cub, hit);
	select_shortest_hitpoint(hit, cub);
	update_data(hit, cub);
}

void	get_vertical_hit(t_cub *cub, t_hit *hit)
{
	double	x_step_v;
	double	y_step_v;

	x_step_v = 1;
	y_step_v = tan(cub->cur_angle * (M_PI / 180));
	if (cub->left)
		x_step_v *= -1;
	if (cub->up && y_step_v > 0)
		y_step_v *= -1;
	else if (cub->down && y_step_v < 0)
		y_step_v *= -1;
	get_initial_vhit(hit, cub);
	while (!hit->v_hit)
	{
		hit->v_hitx += x_step_v;
		hit->v_hity += y_step_v;
		if (!check_if_hit_v(hit, cub))
			break ;
	}
}

void	get_horizontal_hit(t_cub *cub, t_hit *hit)
{
	double	x_step_h;
	double	y_step_h;

	x_step_h = 1 / tan(cub->cur_angle * (M_PI / 180));
	y_step_h = 1;
	if (cub->left && x_step_h > 0)
		x_step_h *= -1;
	else if (cub->right && x_step_h < 0)
		x_step_h *= -1;
	if (cub->up)
		y_step_h *= -1;
	get_initial_hhit(hit, cub);
	while (!hit->h_hit)
	{
		hit->h_hitx += x_step_h;
		hit->h_hity += y_step_h;
		if (!check_if_hit_h(hit, cub))
			break ;
	}
}

void	select_shortest_hitpoint(t_hit *hit, t_cub *cub)
{
	double	h_distance;
	double	v_distance;

	h_distance = 0;
	v_distance = 0;
	if (hit->h_hit)
		h_distance = distance(hit->h_hitx, cub->posx, hit->h_hity, cub->posy);
	if (hit->v_hit)
		v_distance = distance(hit->v_hitx, cub->posx, hit->v_hity, cub->posy);
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

double	distance(double x1, double x2, double y1, double y2)
{
	double	distance;

	distance = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	return (distance);
}
