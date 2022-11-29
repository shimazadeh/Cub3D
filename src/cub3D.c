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
	mlx_hook(cub->win_ptr, 2, 1L << 0, &key_hook, cub);
	mlx_hook(cub->win_ptr, 33, 131072, &ft_exit, cub);
	mlx_loop_hook(cub->mlx_ptr, &handle_no_event, NULL);
	cub3D_render_pos(cub, hit);
	mlx_loop(cub->mlx_ptr);
}

void	cub3D_render_pos(t_cub *cub, t_hit *hit)
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
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->mlx_img, 0, 0);
}

void	get_cur_angle_and_dir(t_cub *cub, int i)
{
	cub->right = false;
	cub->left = false;
	cub->up = false;
	cub->down = false;
	cub->cur_angle = ((double)cub->base_angle + ((double)i / (double)cub->width) * 66);
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
	// printf("CUR ANGLE = %f THETA = %f DIST %f PWDIST = %f\n", cub->cur_angle, theta, cub->dist, cub->pwdist);
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
	int	wall_height;
	int	start;
	int	j;
	int	k;
	double	offset;

	offset = 0;
	k = i + 1;
	wall_height = ((WINDOW_WIDTH / 2) / tan(33 * M_PI / 180)) / cub->pwdist;
	start = (WINDOW_LENGTH / 2) - wall_height / 2;
	// if (start < 0)
	// 	start = 0;
	while (i < k)
	{
		j = 0;
		while (j < start)
		{
			img_pix_put(cub, cub->img, i, j, cub->fl);
			j++;
		}
		while (j < start + wall_height) // && j < 1080 - start)
		{
			if (cub->cur_text == 'n')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->no, 128 / wall_height, &offset, cub->text_offset));
			else if (cub->cur_text == 'e')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->ea, 128 / wall_height, &offset, cub->text_offset));
			else if (cub->cur_text == 's')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->so, 128 / wall_height, &offset, cub->text_offset));
			else if (cub->cur_text == 'w')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->we, 128 / wall_height, &offset, cub->text_offset));
			j++;
		}
		while (j < 1080)
		{
			img_pix_put(cub, cub->img, i, j, cub->ce);
			j++;
		}
		i++;
	}
	if (cub->prev_text == cub->cur_text)
		cub->text_offset += 128 / wall_height;
	else
		cub->text_offset = 0;
}

int	get_pix(void *img, double ratio, double *offset, double text_offset)
{
	int	pixel;

	pixel = ((int *)img)[(int)text_offset * 128 + *(int *)offset];
	printf("%d\n", (int)text_offset * 128 + *(int *)offset);
	*offset += ratio;
	return (pixel);
}
