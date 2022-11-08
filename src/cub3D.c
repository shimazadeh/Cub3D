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

	i = cub->width;
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

void	get_cur_angle(t_cub *cub, int i)
{
	cub->cur_angle = (cub->base_angle + ((cub->width - i) / cub->width) * 66);
	if (cub->cur_angle > 360)
		cub->cur_angle -= 360;
	else if (cub->cur_angle < 0)
		cub->cur_angle += 360;
}

void	get_next_hitpoint(t_cub *cub, t_hit *hit)
{
	int	i;

	i = -1;
	while (!hit->v_hit || !hit->h_hit)
	{
		get_next_vhit(++i, hit, cub);
		get_next_hhit(i, hit, cub);
	}
	if (hit->v_hit && hit->h_hit)
		select_shortest_hitpoint(hit, cub);
	if (hit->v_hit)
	{
		cub->hitX = hit->v_hitX;
		cub->hitY = hit->v_hitY;
		if (cub->cur_angle < 90 && cub->cur_angle > 270)
			cub->cur_text = 'E';
		else
			cub->cur_text = 'W';
	}
	else
	{
		cub->hitX = hit->h_hitX;
		cub->hitY = hit->h_hitY;
		if (cub->cur_angle < 180)
			cub->cur_text = 'N';
		else
			cub->cur_text = 'S';
	}
}

void	get_next_vhit(int i, t_hit *hit, t_cub *cub)
{
	double	x;
	double	y;
	double	adj;
	
	if (cub->cur_angle == 90 || cub->cur_angle == 270)
		return ;
	if (cub->cur_angle < 90)
	{
		x = round(cub->posX) + i + 0.5;
		adj = x - cub->posX;
	}
	else
	{
		x = round(cub->posX) - i - 0.5;
		adj = cub->posX - x;
	}
	y = adj * tan(cub->base_angle);
	check_if_hit(cub->map, x, y, hit);
}

void	get_next_hhit(int i, t_hit *hit, t_cub *cub)
{
	double	x;
	double	y;
	double	adj;
	
	if (cub->cur_angle == 0 || cub->cur_angle == 180)
		return ;
	if (cub->cur_angle < 180)
	{
		y = round(cub->posY) + i + 0.5;
		adj = y - cub->posY;
	}
	else
	{
		y = round(cub->posX) - i - 0.5;
		adj = cub->posY - y;
	}
	x = adj * tan(cub->base_angle);
	check_if_hit(cub->map, x, y, hit);	
}

void	select_shortest_hitpoint(t_hit *hit, t_cub *cub)
{
	
}