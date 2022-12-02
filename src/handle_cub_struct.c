/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cub_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:53:32 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/21 16:02:47 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub_struct(t_cub *cub)
{
	init_cub_parameter(cub);
	init_img_struct(cub->img);
	init_img_struct(cub->img_no);
	init_img_struct(cub->img_so);
	init_img_struct(cub->img_ea);
	init_img_struct(cub->img_we);
	cub->right = false;
	cub->left = false;
	cub->up = false;
	cub->down = false;
}

void	init_cub_parameter(t_cub *cub)
{
	cub->hookx = 0;
	cub->hooky = 0;
	cub->hookangle = 0;
	cub->ret = 0;
	cub->fd = 0;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->fl = 0;
	cub->ce = 0;
	cub->map = NULL;
	cub->height = 1080;
	cub->width = 1920;
	cub->posx = 0;
	cub->posy = 0;
	cub->base_angle = 0;
	cub->cur_angle = 0;
	cub->hitx = 0;
	cub->hity = 0;
	cub->pwdist = 0;
	cub->dist = 0;
	cub->cur_text = 0;
	cub->prev_text = 0;
	cub->text_offset = 0;
}

void	init_img_struct(t_im *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bps = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	destroy_cub_struct(t_cub *cub)
{
	if (cub->win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->img_no->mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->img_no->mlx_img);
	if (cub->img_so->mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->img_so->mlx_img);
	if (cub->img_ea->mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->img_ea->mlx_img);
	if (cub->img_we->mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->img_we->mlx_img);
	if (cub->img->mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->img->mlx_img);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	if (cub->map)
		free_tab(cub->map);
}
