/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:56:14 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/29 16:35:44 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub3d(t_cub *cub)
{
	t_hit	hit[1];

	init_hit_struct(hit);
	cub->hit_str = hit;
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->width, cub->height, "lol");
	if (!cub->win_ptr)
	{
		ft_putstr_fd("Error\nWindow could not be created!\n", 2);
		return ;
	}
	cub->img->mlx_img = mlx_new_image(cub->mlx_ptr, cub->width, cub->height);
	cub->img->addr = mlx_get_data_addr(cub->img->mlx_img, &cub->img->bps, \
	&cub->img->line_length, &cub->img->endian);
	mlx_hook(cub->win_ptr, 2, 1L << 0, &key_hook, cub);
	mlx_hook(cub->win_ptr, 33, 131072, &ft_exit, cub);
	mlx_loop_hook(cub->mlx_ptr, &handle_no_event, NULL);
	cub3d_render_pos(cub, hit);
	mlx_loop(cub->mlx_ptr);
}

void	cub3d_render_pos(t_cub *cub, t_hit *hit)
{
	int	i;

	i = 0;
	cub->posx = cub->hookx;
	cub->posy = cub->hooky;
	cub->base_angle = cub->hookangle;
	while (i < cub->width)
	{
		get_cur_angle_and_dir(cub, i);
		init_hit_struct(hit);
		get_next_hitpoint(cub, hit);
		get_perpwalldist(cub);
		draw_line(1920 - i, cub);
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, \
	cub->img->mlx_img, 0, 0);
}

void	get_cur_angle_and_dir(t_cub *cub, int i)
{
	cub->right = false;
	cub->left = false;
	cub->up = false;
	cub->down = false;
	cub->cur_angle = ((double)cub->base_angle + \
	((double)i / (double)cub->width) * 66);
	if (cub->cur_angle > 360)
		cub->cur_angle -= 360;
	else if (cub->cur_angle < 0)
		cub->cur_angle += 360;
	if (cub->cur_angle >= 0 && cub->cur_angle <= 180)
		cub->up = true;
	else
		cub->down = true;
	if (cub->cur_angle >= 270 || cub->cur_angle <= 90)
		cub->right = true;
	else
		cub->left = true;
}

void	init_hit_struct(t_hit *hit)
{
	hit->v_hit = false;
	hit->h_hit = false;
	hit->v_hitx = 0;
	hit->v_hity = 0;
	hit->v_text = 0;
	hit->h_hitx = 0;
	hit->h_hity = 0;
	hit->h_text = 0;
}

void	get_perpwalldist(t_cub *cub)
{
	double	theta;

	theta = cub->cur_angle - ((double)cub->base_angle - 57);
	if (theta > 360)
		theta -= 360;
	else if (theta < 0)
		theta += 360;
	cub->pwdist = sqrt(cub->dist) * sin(theta * (M_PI / 180));
}
