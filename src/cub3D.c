/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:56:14 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/21 17:08:06 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub3D(t_cub *cub)
{
	t_hit	hit[1];
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (cub->map[i])
		i++;
	while (cub->map[0][j])
		j++;
	cub->maph = i;
	cub->mapw = j;
	init_hit_struct(hit);
	
	cub->hit_str = hit;
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->width, cub->height, "lol");
	if (!cub->win_ptr)
	{
		ft_putstr_fd("Error\nWindow could not be created!\n", 2);
		return ;
	}
	cub->img->mlx_img = mlx_new_image(cub->mlx_ptr, cub->width, cub->height);
	cub->img->addr = mlx_get_data_addr(cub->img->mlx_img, &cub->img->bps, &cub->img->line_length, &cub->img->endian);
	
	
	mlx_hook(cub->win_ptr, 2, 1L<<0, &key_hook, cub);
	mlx_hook(cub->win_ptr, 33, 131072, &ft_exit, cub);
	mlx_loop_hook(cub->mlx_ptr, &handle_no_event, NULL);
	cub3D_render_pos(cub, hit);

	
	mlx_loop(cub->mlx_ptr);
	cub3D_render_pos(cub, hit);
}

void	cub3D_render_pos(t_cub *cub, t_hit *hit)
{
	int	i;

	i = 0;
	cub->posX = cub->hookX;
	cub->posY = cub->hookY;
	cub->base_angle = cub->hookangle;
	while (i < cub->width)
	{
		get_cur_angle_and_dir(cub, i);
		init_hit_struct(hit);
		get_next_hitpoint(cub, hit);
		get_perpwalldist(cub);
		draw_line(i, cub);
		i += 16;
	}
	mlx_put_image_to_window(cub->mlx_ptr,cub->win_ptr, cub->img->mlx_img, 0, 0);
}

void	get_cur_angle_and_dir(t_cub *cub, int i)
{
	cub->right = false;
	cub->left = false;
	cub->up = false;
	cub->down = false;
	cub->cur_angle = (cub->base_angle + ((cub->width - i) / cub->width) * 66);
	if (cub->cur_angle > 360)
		cub->cur_angle -= 360;
	else if (cub->cur_angle < 0)
		cub->cur_angle += 360;
	if (cub->cur_angle > 0 && cub->cur_angle < 180)
		cub->up = 1;
	else
		cub->down = 1;

	if (cub->cur_angle > 270 || cub->cur_angle < 90)
		cub->right = 1;
	else
		cub->left = 1;
}

void	get_next_hitpoint(t_cub *cub, t_hit *hit)
{
	double	x_step_h;
	double	y_step_h;
	double	x_step_v;
	double	y_step_v;
	
	x_step_v = 1;
	y_step_v = tan(cub->cur_angle);
	x_step_h = 1 / tan(cub->cur_angle); //1 is the tile size
	y_step_h = 1;
	
	get_initial_vhit(hit, cub);
	get_initial_hhit(hit, cub);
	while(!hit->v_hit && !hit->h_hit)
	{
		hit->v_hitX += x_step_v;
 		hit->v_hitY += y_step_v;
		hit->h_hitX += x_step_h;
		hit->h_hitY += y_step_h;
		check_if_hit_v(hit, cub);
		check_if_hit_h(hit, cub);
	}
	select_shortest_hitpoint(hit, cub);
	update_data(hit, cub);
}

void	init_hit_struct(t_hit *hit)
{
	hit->v_hit = false;
	hit->h_hit = false;
	hit->v_hitX = 0;
	hit->v_hitY = 0;
	hit->v_text = 0;
	hit->h_hitX = 0;
	hit->h_hitY = 0;
	hit->h_text = 0;
}

void	get_perpwalldist(t_cub *cub)
{
	double	theta;

	theta = cub->base_angle - 57;
	if (theta > 359)
		theta -= 360;
	else if (theta < 0)
		theta += 360;
	cub->pwdist = cub->dist * cos(theta);
}

void	img_pix_put(t_cub *cub, t_im *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= 0 && x < cub->width && y >= 0 && y < cub->height)
	{
		i = img->bps - 8;
		pixel = img->addr + (y * img->line_length + x
				* (img->bps / 8));
		while (i >= 0)
		{
			if (img->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (img->bps - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
	return ;
}

void	draw_line(int i, t_cub *cub)
{
	int	size;
	int	start;
	int	j;
	int	k;

	k = i + 16;
	size = 128 / cub->pwdist;
	start = 540 - size / 2;
	while (i < k)
	{
		j = 0;
		while (j < start)
		{
			img_pix_put(cub, cub->img, i, j, cub->fl);
			j++;
		}
		while (j < start + size)
		{
			img_pix_put(cub, cub->img, i, j, 256);
			j++;
		}
		while (j < 1080)
		{
			img_pix_put(cub, cub->img, i, j, cub->ce);
			j++;
		}
		i++;
	}
}
